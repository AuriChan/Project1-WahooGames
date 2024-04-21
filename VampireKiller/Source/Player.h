#pragma once
#include "Entity.h"
#include "TileMap.h"

#define PLAYER_FRAME_SIZE_X		48
#define PLAYER_FRAME_SIZE_Y     32
#define PLAYER_FRAME_SIZE_WHIP  64

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
#define PLAYER_JUMP_FORCE		9

//Frame delay for updating the jump velocity
#define PLAYER_JUMP_DELAY		2

//Player is levitating when abs(speed) <= this value
#define PLAYER_LEVITATING_SPEED	4

//Gravity affects jumping velocity when jump_delay is 0
#define GRAVITY_FORCE			1

//Logic states
enum class State { IDLE, WALKING, JUMPING, FALLING, CROUCHING, CLIMBING, ATTACKING, DEAD };
enum class Look { RIGHT, LEFT};

enum class PlayerAnim {
	IDLE_LEFT, IDLE_RIGHT, IDLE_BACK,
	WALKING_LEFT, WALKING_RIGHT, 
	JUMPING_LEFT, JUMPING_RIGHT,
	FALLING_LEFT, FALLING_RIGHT,
	CROUCHING_LEFT, CROUCHING_RIGHT,
	CLIMBING_TOP_LEFT, CLIMBING_TOP_RIGHT,
	CLIMBING_BOTTOM_LEFT, CLIMBING_BOTTOM_RIGHT,
	RECEIVING_DAMAGE, DEATH,
	WHIP_IDLE_LEFT, WHIP_IDLE_RIGHT,
	WHIP_JUMPING_LEFT, WHIP_JUMPING_RIGHT,
	WHIP_CROUCHING_LEFT, WHIP_CROUCHING_RIGHT,
	WHIP_CLIMBING_TOP_LEFT, WHIP_CLIMBING_TOP_RIGHT,
	WHIP_CLIMBING_BOTTOM_LEFT, WHIP_CLIMBING_BOTTOM_RIGHT,
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
	void IncrScore(int n);
	void IncrLifes(int n);
	int GetScore();
	void SetLifes(int l);
	int GetLives()const;
	bool GetWin();
	void SetWin(bool w);

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
	/*void LogicClimbing();*/

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
	/*void StartClimbingUp();
	void StartClimbingDown();*/
	void ChangeAnimRight();
	void ChangeAnimLeft();

	//Jump steps
	bool IsAscending() const;
	bool IsLevitating() const;
	bool IsDescending() const;

	//Ladder get in/out steps
	bool IsInFirstHalfTile() const;
	bool IsInSecondHalfTile() const;

	State state;
	Look look;
	int jump_delay;

	TileMap* map;
	int stageC;
	int score;
	int lifes = 3;
	bool win = false;
	bool isFinished = false;
};

