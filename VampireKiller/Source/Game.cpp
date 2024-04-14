#include "Game.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <stdio.h>

Game::Game()
{
    state = GameState::MAIN_MENU;
    scene = nullptr;
    img_menu = {};

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
    InitWindow((int)w, (int)h, "VampireKiller");

    //Render texture initialisation, used to hold the rendering result so we can easily resize it
    target = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (target.id == 0)
    {
        LOG("Failed to create render texture");
        return AppStatus::ERROR;
    }
  
    src = { 0, 0, WINDOW_WIDTH, -WINDOW_HEIGHT };
    dst = { 0, 0, w, h };

    //Load resources
    if (LoadResources() != AppStatus::OK)
    {
        LOG("Failed to load textures");
        return AppStatus::ERROR;
    }

    //Set the target frame rate for the application
    SetTargetFPS(60);

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
    if (scene->Init() == AppStatus::ERROR)
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
    switch (state)
    {
    case GameState::MAIN_MENU:
        if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
        if (IsKeyPressed(KEY_SPACE))
        {
            if (BeginPlay() == AppStatus::ERROR) return AppStatus::ERROR;
            state = GameState::PLAYING;
        }
        break;

    case GameState::PLAYING:
        if (IsKeyPressed(KEY_ESCAPE))
        {
            FinishPlay();
            state = GameState::MAIN_MENU;
        }
        else
        {
            //Process Input
            scene->HandleInputPlayer();
            //Game logic
            scene->Update();
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

    UnloadRenderTexture(target);
}