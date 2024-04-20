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
    float w, h;
    w = WINDOW_WIDTH * scale;
    h = WINDOW_HEIGHT * scale;

    //Initialise window
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
    dst = { 0, 0, w, h };

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

    return AppStatus::OK;
}
AppStatus Game::LoadResources()
{
    ResourceManager& data = ResourceManager::Instance();

    if (data.LoadTexture(Resource::IMG_MENU, "Images/TitleScreen.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_menu = data.GetTexture(Resource::IMG_MENU);

    if (data.LoadTexture(Resource::IMG_DATA, "Images/InitialScreen.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_initialScreen = data.GetTexture(Resource::IMG_DATA);

    if (data.LoadTexture(Resource::IMG_DEATH, "Images/game over.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_death = data.GetTexture(Resource::IMG_DEATH);

    if (data.LoadTexture(Resource::IMG_WIN, "Images/EndCredits.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_win = data.GetTexture(Resource::IMG_WIN);

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
    if (WindowShouldClose()) return AppStatus::QUIT;

    switch (state)
    {
    case GameState::INITIAL_SCREEN:
        if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
        if (IsKeyPressed(KEY_SPACE))
        {
            state = GameState::MAIN_MENU;
        }
        break;

    case GameState::MAIN_MENU:
        if (IsKeyPressed(KEY_ESCAPE)) { return AppStatus::QUIT; };
        if (IsKeyPressed(KEY_SPACE))
        {
            if (BeginPlay() != AppStatus::OK) return AppStatus::ERROR;
            state = GameState::PLAYING;
        }
        break;
    case GameState::PLAYING:
        if (IsKeyPressed(KEY_ESCAPE))
        {
       
            FinishPlay();
            state = GameState::MAIN_MENU;
        }
        
        else if (IsKeyPressed(KEY_D))
        {
            state = GameState::DEATH;
        }
        else if (IsKeyPressed(KEY_W))
        {
            state = GameState::WIN;
        }
        else if (scene->GetPlayer()->GetLives() == 0)
        {
            state = GameState::DEATH;
        }
       
       
        else 
        {
            //Game logic
            scene->Update();
        }
        break;
    case GameState::DEATH:
        if (IsKeyPressed(KEY_ESCAPE)) { state = GameState::MAIN_MENU; };
        if (IsKeyPressed(KEY_SPACE))
        {
            state = GameState::MAIN_MENU;
        }
        break;
    case GameState::WIN:
        if (IsKeyPressed(KEY_ESCAPE)) { state = GameState::MAIN_MENU; };
        if (IsKeyPressed(KEY_SPACE))
        {
            state = GameState::MAIN_MENU;
        }
        break;
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
        
        /*Rectangle s;
        s.x = 0;
        s.y = 0;
        s.width = 692;
        s.height = 520;

        Rectangle d;
        d.x = 0;
        d.y = 0;
        d.width = 256;
        d.height = 208;
        Vector2 v;
        v.x = 0;
        v.y = 0;

        DrawTexturePro(*img_initialScreen, s, d, v, 0, WHITE);*/
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
    EndDrawing();
}
void Game::Cleanup()
{
    UnloadResources();
    CloseWindow();
}
void Game::UnloadResources()
{
    ResourceManager& data = ResourceManager::Instance();
    data.ReleaseTexture(Resource::IMG_MENU);

    data.ReleaseTexture(Resource::IMG_WIN);
    
    data.ReleaseTexture(Resource::IMG_DEATH);
    
    data.ReleaseTexture(Resource::IMG_DATA);

    UnloadRenderTexture(target);
}