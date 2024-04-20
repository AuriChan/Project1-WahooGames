#pragma once
#include "Entity.h"
#include "TileMap.h"

#define ENEMY_FRAME_SIZE_X		16
#define ENEMY_FRAME_SIZE_Y      32

//Logical model size: 12x28
#define ENEMY_PHYSICAL_WIDTH	12
#define ENEMY_PHYSICAL_HEIGHT	28

//Horizontal speed and vertical speed while falling down
#define ENEMY_SPEED			1




//Logic states
enum class eState { IDLE, WALKING, ATTACKING, DEAD, WAIT };
enum class eLook { RIGHT, LEFT};

enum class EnemyAnim {
	IDLE_LEFT, IDLE_RIGHT,
	WALKING_LEFT, WALKING_RIGHT,
	RECEIVING_DAMAGE, DEATH,
	NUM_ANIMATIONS
};
class Enemy : public Entity
{
public:
	Enemy(const Point& p, eState s, eLook view);
	~Enemy();

	AppStatus Initialise();
	void SetTileMap(TileMap* tilemap);


	
	void SetStage(int n);
	int GetStage()const;
	eState GetState()const;
	void SetState(eState s);

	
	
	void SetLifes(int l);
	int GetLives()const;

	void Update(int marginLeft, int marginRight);
	void DrawDebug(const Color& col) const;
	void Release();

private:
	bool IsLookingRight() const;
	bool IsLookingLeft() const;

	//Enemy mechanics
	void MoveX(int ml, int mr);
	
	
	

	//Animation management
	void SetAnimation(int id);
	EnemyAnim GetAnimation();
	void Stop();
	void StartWalkingLeft();
	void StartWalkingRight();
	void ChangeAnimRight();
	void ChangeAnimLeft();


	eState state;
	eLook look;
	

	TileMap* map;
	int stageC;
	bool lookLeft = true;
	bool lookRight = false;
	int lifes = 1;
};

