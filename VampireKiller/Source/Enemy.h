#pragma once
#include "Entity.h"

#define BAT_WIDTH 16;
#define BAT_HEIGHT 48;
#define SKULL_HEAD_SIZE 16;
#define SKULL_TURRET_WIDTH 16;
#define SKULL_TURRET_HEIGTH 32;

#define SOLDIER_FRAME_SIZE_Y 32;
#define SOLDIER_FRAME_SIZE_X 16;
#define SOLDIER_WIDTH 16;
#define SOLDIER_HEIGHT 32;

enum class EnemyType { SLIME, TURRET };

class Enemy : public Entity
{
public:
	Enemy(const Point& p, int width, int height, int frame_width, int frame_height);
	virtual ~Enemy();

	//Draw the maximum visibility area of the enemy
	void DrawVisibilityArea(const Color& col) const;

	//Pure virtual functions, any class inheriting from this class must provide its own implementations

	//Initialize the enemy with the specified look and area
	virtual AppStatus Initialise(LookE look, const AABB& area) = 0;

	//Update the enemy according to its logic, return true if the enemy must shoot
	virtual bool Update(const AABB& box) = 0;

	//Retrieve the position and direction of the shot to be thrown
	virtual void GetShootingPosDir(Point* pos, Point* dir) const = 0;

protected:
	//Return true if the given hitbox is within the visibility area and the enemy is facing it
	bool IsVisible(const AABB& hitbox);

	LookE look;
	AABB visibility_area;
};

