#pragma once
#include "Globals.h"
#include "Scene.h"
#include "FadeTransition.h"

//enum class GameState { DEATH, WIN, INITIAL_SCREEN, MAIN_MENU, PLAYING, SETTINGS, CREDITS };

class Game
{
public:
    Game();
    ~Game();

    AppStatus Initialise(float scale);
    AppStatus Update();
    void Render();
    void Cleanup();

private:
    AppStatus BeginPlay();
    void FinishPlay();
    void FullScreenWindow(int windowWidth, int windowHeight);
    AppStatus LoadResources();
    void UnloadResources();
 
    GameState state;
    Scene* scene;
    const Texture2D* img_menu;
    const Texture2D* img_initialScreen;
    const Texture2D* img_death;
    const Texture2D* img_win;

    //To work with original game units and then scale the result
    RenderTexture2D target;
    Rectangle src, dst;
    ResourceManager& data = ResourceManager::Instance();

    FadeTransition fade_transition;
};