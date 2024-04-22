#pragma once
#include <raylib.h>
#include "Player.h"
#include "TileMap.h"
#include "Object.h"
#include "Enemy.h"


enum class DebugMode { OFF, SPRITES_AND_HITBOXES, ONLY_HITBOXES, SIZE };

class Scene
{
public:
    Scene();
    ~Scene();

    AppStatus Init();
    void Update();
    void Render();
    void Release();
    Player* GetPlayer()const;
  
    Music GetMusic(int i) const;
    

private:
    AppStatus LoadLevel(int stage);

    void CheckCollisions();
    void ClearLevel();
    void RenderObjects() const;
    void RenderObjectsDebug(const Color& col) const;

    void RenderGUI() const;

    Player* player;
   
    TileMap* level;
 
    std::vector<Object*> objects;
    std::vector<Object*> objects2;
    
    Camera2D camera;
    DebugMode debug;
    int marginLeft =ENEMY_FRAME_SIZE_X * 5;
    int marginRight = (WINDOW_WIDTH - ENEMY_FRAME_SIZE_X * 4);
   

    Music musics[10];
    Sound sound;
    
    

  

};
