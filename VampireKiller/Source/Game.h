#pragma once
#include "Globals.h"
#include "Scene.h"


enum class GameState { MAIN_MENU, PLAYING, DEATH, WIN };

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

    AppStatus LoadTextures();
    void UnloadTextures();

    GameState state;
    Scene* scene;
    Texture2D img_menu;

    //To work with original game units and then scale the result
    RenderTexture2D target;
    Rectangle src, dst;
};