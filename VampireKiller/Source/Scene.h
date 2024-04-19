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
    

private:
    AppStatus LoadLevel(int stage);

    void CheckCollisions();
    void ClearLevel();
    void RenderObjects() const;
    void RenderObjectsDebug(const Color& col) const;

    void RenderGUI() const;

    Player* player;
    Enemy* soldier;
    TileMap* level;
 
    std::vector<Object*> objects;
    Sprite* fire;
    
    Camera2D camera;
    DebugMode debug;
};
