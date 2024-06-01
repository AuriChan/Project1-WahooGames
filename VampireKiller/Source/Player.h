#pragma once
#include "Entity.h"
#include "TileMap.h"

#define PLAYER_FRAME_SIZE_X	    80
#define PLAYER_FRAME_SIZE_Y     32

//Logical model size: 12x28
#define PLAYER_PHYSICAL_WIDTH	12
#define PLAYER_PHYSICAL_HEIGHT	28

//Horizontal speed and vertical speed while falling down
#define PLAYER_SPEED			1

//Vertical speed while on a ladder
#define PLAYER_LADDER_SPEED		1

//Frame animation delay while on a ladder
#define ANIM_LADDER_DELAY		(2*ANIM_DELAY)

//When jumping, initial jump speed and maximum falling speed
#define PLAYER_JUMP_FORCE		8

//Frame delay for updating the jump velocity
#define PLAYER_JUMP_DELAY		2

//Player is levitating when abs(speed) <= this value
#define PLAYER_LEVITATING_SPEED	4

//Gravity affects jumping velocity when jump_delay is 0
#define GRAVITY_FORCE			1

//Logic states
enum class State { IDLE, WALKING, JUMPING, FALLING, CROUCHING, CLIMBING, ATTACKING, DEAD };


enum class PlayerAnim {
	IDLE_LEFT, IDLE_RIGHT, IDLE_BACK,
	WALKING_LEFT, WALKING_RIGHT, 
	JUMPING_LEFT, JUMPING_RIGHT,
	FALLING_LEFT, FALLING_RIGHT,
	CROUCHING_LEFT, CROUCHING_RIGHT,
	CLIMBING_TOP_RIGHT, CLIMBING_BOTTOM_LEFT,
	RECEIVING_DAMAGE, DEATH_LEFT, DEATH_RIGHT,
	WHIP_IDLE_LEFT, WHIP_IDLE_RIGHT,
	WHIP_CROUCHING_LEFT, WHIP_CROUCHING_RIGHT,
	WHIP_CLIMBING_TOP_RIGHT, WHIP_CLIMBING_BOTTOM_LEFT,
	NUM_ANIMATIONS
};
class Player : public Entity
{
public:
	Player(const Point& p, State s, Look view);
	~Player();

	AppStatus Initialise();
	void SetTileMap(TileMap* tilemap);
	

	void InitScore();
	void SetStage(int n);
	int GetStage()const;

	void SetLevel(int n);
	int GetLevel()const;

	void IncrScore(int n);
	void IncrLifes(int n);
	int GetScore()const;
	void SetLifes(int l);
	int GetLives()const;
	bool GetWin()const;
	void SetWin(bool w);

	void SetFCount(int l);
	int GetFCount()const;
	void DecreaseFCount();

	bool GetOrb()const;
	void SetOrb(bool w);

	bool GetKey()const;
	void SetKey(bool k);

	bool GetTreasureKey()const;
	void SetTreasureKey(int k);
	
	

	void SetHp(int h);
	int GetHp()const;
	int GetPosY()const;
	int GetPosx()const;
	AABB GetWhipHitbox();
	
	


	void Update();
	void DrawDebug(const Color& col) const;
	void Release();

private:
	bool IsLookingRight() const;
	bool IsLookingLeft() const;

	//Player mechanics
	void MoveX();
	void MoveY();
	void LogicJumping();
	void LogicClimbing();

	//Animation management
	void SetAnimation(int id);
	PlayerAnim GetAnimation();
	void Stop();
	void StartWalkingLeft();
	void StartWalkingRight();
	void StartFalling();
	void StartJumping();
	void StartCrouching();
	void StartAttacking();
	void StartClimbingUp();
	void StartClimbingDown();
	void Death();
	
	void ChangeAnimRight();
	void ChangeAnimLeft();

	//Jump steps
	bool IsAscending() const;
	bool IsLevitating() const;
	bool IsDescending() const;

	//Ladder get in/out steps
	/*bool IsInFirstHalfTile() const;
	bool IsInSecondHalfTile() const;*/

	State state;
	Look look;
	int jump_delay;
	int Level = 0;

	TileMap* map;
	int stageC = 1;
	int score;
	int lifes = 3;
	int HpBar = 1088;
	bool win = false;
	bool key = false;
	bool treasureKey = false;
	bool TKey1 = false;
	bool isFinished = false;
	bool isCrouching = false;
	ResourceManager& data = ResourceManager::Instance();

	AABB whipbox;
	bool isClimbingUp;
	bool isClimbingDown;
	bool startedClimbing;
	int timer = 0;
	int hitTimer = 0;
	bool hit = false;
	bool spawnOrb = false;

	int finalCountdown = -1;
};

