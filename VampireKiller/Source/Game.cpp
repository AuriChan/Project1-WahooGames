#include "Game.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <stdio.h>


Game::Game()
{
    
    state = GameState::INITIAL_SCREEN;
    scene = nullptr;
    img_menu = nullptr;
    img_initialScreen = nullptr;
    img_death = nullptr;
    img_win = nullptr;

    target = {};
    src = {};
    dst = {};
}
Game::~Game()
{
    if (scene != nullptr)
    {
        scene->Release();
        delete scene;
        scene = nullptr;
    }
}
AppStatus Game::Initialise(float scale)
{
    InitAudioDevice();
    float w, h;
    w = WINDOW_WIDTH * scale;
    h = WINDOW_HEIGHT * scale;

    //Initialise window
    int monitor = GetCurrentMonitor();
     InitWindow((int)w, (int)h, "Vampire Killer");
     

    //Render texture initialisation, used to hold the rendering result so we can easily resize it
    target = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (target.id == 0)
    {
        LOG("Failed to create render texture");
        return AppStatus::ERROR;
    }
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
    src = { 0, 0, WINDOW_WIDTH, -WINDOW_HEIGHT };
    dst = { 0 , 0, WINDOW_WIDTH * scale, WINDOW_HEIGHT * scale };

    //Load resources
    if (LoadResources() != AppStatus::OK)
    {
        LOG("Failed to load resources");
        return AppStatus::ERROR;
    }


    //Set the target frame rate for the application
    SetTargetFPS(60);
    //Disable the escape key to quit functionality
    SetExitKey(0);

    
        FullScreenWindow(WINDOW_WIDTH * GAME_SCALE_FACTOR, WINDOW_HEIGHT * GAME_SCALE_FACTOR);

    
    
   

    return AppStatus::OK;
}
AppStatus Game::LoadResources()
{
    ResourceManager& data = ResourceManager::Instance();

    if (data.LoadTexture(ResourceImages::IMG_MENU, "Images/TitleScreen.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_menu = data.GetTexture(ResourceImages::IMG_MENU);

    if (data.LoadTexture(ResourceImages::IMG_DATA, "Images/InitialScreen.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_initialScreen = data.GetTexture(ResourceImages::IMG_DATA);

    if (data.LoadTexture(ResourceImages::IMG_DEATH, "Images/game over.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_death = data.GetTexture(ResourceImages::IMG_DEATH);

    if (data.LoadTexture(ResourceImages::IMG_WIN, "Images/EndCredits.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_win = data.GetTexture(ResourceImages::IMG_WIN);

    return AppStatus::OK;
}
AppStatus Game::BeginPlay()
{
    scene = new Scene();
    if (scene == nullptr)
    {
        LOG("Failed to allocate memory for Scene");
        return AppStatus::ERROR;
    }
    if (scene->Init() != AppStatus::OK)
    {
        LOG("Failed to initialise Scene");
        return AppStatus::ERROR;
    }

    return AppStatus::OK;
}
void Game::FinishPlay()
{
    scene->Release();
    delete scene;
    scene = nullptr;
}
AppStatus Game::Update()
{
    //Check if user attempts to close the window, either by clicking the close button or by pressing Alt+F4
    
    if (IsKeyPressed(KEY_ENTER))
    {
        FullScreenWindow(WINDOW_WIDTH * GAME_SCALE_FACTOR, WINDOW_HEIGHT * GAME_SCALE_FACTOR);

    }
       
    

    if (WindowShouldClose()) return AppStatus::QUIT;

    if (fade_transition.IsActive() == true)
    {
        GameState prev_frame = state;
        state = fade_transition.Update();

        //Begin play and finish play are delayed due to the fading transition effect
        if (prev_frame == GameState::MAIN_MENU && state == GameState::PLAYING)
        {
            if (BeginPlay() != AppStatus::OK) return AppStatus::ERROR;
        }
        else if (prev_frame == GameState::PLAYING && state == GameState::MAIN_MENU)
        {
            FinishPlay();
        }
    }

    else
    {
        switch (state)
        {
        case GameState::INITIAL_SCREEN:
            if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
            if (IsKeyPressed(KEY_SPACE))
            {
                /*state = GameState::MAIN_MENU;*/
                fade_transition.Set(GameState::INITIAL_SCREEN, 5, GameState::MAIN_MENU, 5, dst);
            }
            break;

        case GameState::MAIN_MENU:
            if (IsKeyPressed(KEY_ESCAPE))
            {

                return AppStatus::QUIT;

            };
            if (IsKeyPressed(KEY_SPACE))
            {

                /*if (BeginPlay() != AppStatus::OK) return AppStatus::ERROR;*/
                /*state = GameState::PLAYING;*/
                fade_transition.Set(GameState::MAIN_MENU, 5, GameState::PLAYING, 5, dst);
            }
            break;
        case GameState::PLAYING:

            if (IsKeyPressed(KEY_ESCAPE))
            {
                /*FinishPlay();*/
                fade_transition.Set(GameState::PLAYING, 5, GameState::MAIN_MENU, 5, dst);
                /*state = GameState::MAIN_MENU;*/
                
            }

            else if (IsKeyPressed(KEY_D))
            {
                fade_transition.Set(GameState::PLAYING, 5, GameState::DEATH, 5, dst);
                /*state = GameState::DEATH;*/
            }
            else if (IsKeyPressed(KEY_W))
            {
                fade_transition.Set(GameState::PLAYING, 5, GameState::WIN, 5, dst);
                /*state = GameState::WIN;*/
            }
            else if (scene->GetPlayer()->GetLives() == 0)
            {
                fade_transition.Set(GameState::PLAYING, 5, GameState::DEATH, 5, dst);
                /*state = GameState::DEATH;*/
            }
            else if (scene->GetPlayer()->GetWin() == true)
            {
                fade_transition.Set(GameState::PLAYING, 5, GameState::WIN, 5, dst);
                /*state = GameState::WIN;*/
            }
            else
            {
                //Game logic
                scene->Update();
            }
            break;
        case GameState::DEATH:
            data.StartMusic(ResourceAudio::MUSIC_GAMEOVER);
            if (IsKeyPressed(KEY_ESCAPE)) { state = GameState::MAIN_MENU; };
            if (IsKeyPressed(KEY_SPACE))
            {
               
                state = GameState::MAIN_MENU;
            }
            break;
        case GameState::WIN:
            data.StartMusic(ResourceAudio::MUSIC_ENDING);
            if (IsKeyPressed(KEY_ESCAPE)) { state = GameState::MAIN_MENU; };
            if (IsKeyPressed(KEY_SPACE))
            {
                
                state = GameState::MAIN_MENU;
            }
            break;
        }
    }
    return AppStatus::OK;
}
void Game::Render()
{
    //Draw everything in the render texture, note this will not be rendered on screen, yet
    BeginTextureMode(target);
    ClearBackground(BLACK);

    switch (state)
    {
    case GameState::MAIN_MENU:
        DrawTexture(*img_menu, 0, 0, WHITE);
        
        break;
    case GameState::INITIAL_SCREEN:
        
        DrawTexture(*img_initialScreen, 0, 0, WHITE);
       
       
        break;
    case GameState::WIN:
        DrawTexture(*img_win, 0, 0, WHITE);

        break;
    case GameState::DEATH:
        DrawTexture(*img_death, 0, 0, WHITE);

        break;

    case GameState::PLAYING:
        scene->Render();
        break;
    }

    EndTextureMode();

    //Draw render texture to screen, properly scaled
    BeginDrawing();
    DrawTexturePro(target.texture, src, dst, { 0, 0 }, 0.0f, WHITE);
    if (fade_transition.IsActive()) fade_transition.Render();
    EndDrawing();
}
void Game::Cleanup()
{
    CloseAudioDevice();
    UnloadResources();
    CloseWindow();
}
void Game::UnloadResources()
{
    ResourceManager& data = ResourceManager::Instance();
    data.ReleaseTexture(ResourceImages::IMG_MENU);

    data.ReleaseTexture(ResourceImages::IMG_WIN);
    
    data.ReleaseTexture(ResourceImages::IMG_DEATH);
    
    data.ReleaseTexture(ResourceImages::IMG_DATA);

    UnloadRenderTexture(target);
}
void Game::FullScreenWindow(int windowWidth, int windowHeight)
{
    if (!IsWindowFullscreen())
    {
        int monitor = GetCurrentMonitor();
        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        dst = { (1920 - (WINDOW_WIDTH * 5)) / 2 , 0, WINDOW_WIDTH * 5, WINDOW_HEIGHT * 5 };
        ToggleFullscreen();
    }
    else
    {
        dst = { 0 , 0, WINDOW_WIDTH * GAME_SCALE_FACTOR, WINDOW_HEIGHT * GAME_SCALE_FACTOR };
        ToggleFullscreen();
        SetWindowSize(windowWidth, windowHeight);
    }
}
