#pragma once
#include <raylib.h>
#include "Point.h"
#include "ResourceManager.h"
#include "RenderComponent.h"

/*class Entity
{protected:
	Point GetRenderingPosition() const; // returns a point where the sprite is loaded
    int frame_width, frame_height;//of sprite
	RenderComponent* render;//contains functions to render sprite and hitbox in render position


	Point pos, dir; //pos: element coordinates, dir: direction +/- in x or y
	int width, height; //of hitbox

	
public:
	Entity(const Point& p, int width, int height);//punto de control, width y height de la hitbox
	Entity(const Point& p, int width, int height, int frame_width, int frame_height);//punto de control, width y height de la hitbox, width y height del sprite(frame)
	virtual ~Entity();

	void SetPos(const Point& p);//control point
	void Update(); //move position  into direction
	AABB GetHitbox() const; //returns entity AABB hitbox

	//Draw representation model
	void Draw() const;//gets render positions and uses render to render sprite on said point
	void DrawTint(const Color& col) const; //same as draw but with a color

	//Draw logical/physical model (hitbox)
	void DrawHitbox(const Color& col) const; 
	void DrawHitbox(int x, int y, int w, int h, const Color& col) const;//draws box with the width and height and the sprite mesurements and a color


};*/