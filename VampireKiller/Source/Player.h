#pragma once
#include "Entity.h"
#include "TileMap.h"

#define PLAYER_FRAME_SIZE		32

#define PLAYER_PHYSICAL_WIDTH   12
#define PLAYER_PHYSICAL_HEIGHT  28

#define PLAYER_SPEED            2

#define PLAYER_JUMP_FORCE       10

#define PLAYER_JUMP_DELAY       2

#define PLAYER_LEVITATING_SPEED 4

#define GRAVITY_FORCE           1

enum class State { IDLE, WALKING, JUMPING, FALLING, CLIMBING, DEAD };
enum class Look { RIGHT, LEFT };

enum class PlayerAnim {
	IDLE_LEFT, IDLE_RIGHT, IDLE_BACK,
	WALKING_LEFT, WALKING_RIGHT, 
	JUMPING_LEFT, JUMPING_RIGHT, 
	CROUCHING_LEFT, CROUCHING_RIGHT,
	CLIMBING_TOP_LEFT, CLIMBING_TOP_RIGHT,
	CLIMBING_BOTTOM_LEFT, CLIMBING_BOTTOM_RIGHT,
	RECEIVING_DAMAGE, DEATH,
	WHIP_IDLE_LEFT, WHIP_IDLE_RIGHT,
	WHIP_JUMPING_LEFT, WHIP_JUMPING_RIGHT,
	WHIP_CROUCHING_LEFT, WHIP_CROUCHING_RIGHT,
	WHIP_CLIMBING_TOP_LEFT, WHIP_CLIMBING_TOP_RIGHT,
	WHIP_CLIMBING_BOTTOM_LEFT, WHIP_CLIMBING_BOTTOM_RIGHT
};