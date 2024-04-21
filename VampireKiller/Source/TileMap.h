#pragma once
#include <raylib.h>
#include "Sprite.h"
#include "Globals.h"
#include <unordered_map>
#include "Point.h"
#include "AABB.h"

enum class Tile
{
//BACKGROUND 
	// SOLID 
	CLAY_GROUND = -3, GROUND = -2,
	
	//empty
	EMPTY = -1,
	AIR = 0,
    //1st stage
	FENCE_BOTTOM = 2, FENCE_TOP1, FECNCE_TOP2,
	TREE_LOG_RIGHT = 10,TREE_HANG_LEAF1, TREE_LOG_LEFT, TREE_HANG_LEAF2, TREE_HANG_LEAF3, TREE_HANG_LEAF4, LEAFS_BOTTOM1, LEAFS_BOTTOM2, LEAFS_BOTTOM3, LEAFS_BOTTOM4, LEAFS_BOTTOM5/*20*/,
	LEAFS_BOTTOM6, LEAFS_TOP1, LEAFS_TOP_TREE1, LEAFS_TOP2, LEAFS_TOP3, LEAFS_TOP4, LEAFS_TOP5, LEAFS_TOP6, LEAFS_TOP7, LEAFS_TOP8/*30*/, LEAFS_TOP_TREE2, LEAFS_TOP_TREE3, LEAFS_TOP9,
	LEAFS_TOP_TREE4, LEAFS_TOP_TREE5, LEAFS_TOP10, LEAFS_TOP11, LEAFS_TOP_SKY1, LEAFS_TOP_SKY2, LEAFS_TOP_SKY3/*40*/, LEAFS_TOP_SKY4, LEAFS_TOP_SKY_CASTLE,
	
	TOP_CASTLE1, TOP_CASTLE2,
	MID_CASTLE1, MID_CASTLE2,BROKEN_CASTLE_LEFT, BROKEN_CASTLE_RIGHT, MID_CASTLE3, MID_CASTLE4/*50*/, TOP_WINDOW_LEFT, DOOR_TOP_LEFT, DOOR_TOP_RIGHT, TOP_WINDOW_RIGHT, MID_CASTLE5,
	DOOR_LEFT_BROKEN, DOOR_RIGHT, WINDOW_BOTTOM_LEFT, DOOR_LEFT, DOOR_RIGHT_BROKEN/*60*/, WINDOW_BOTTOM_RIGHT, CASTLE_BOTTOM_LEFT, CASTLE_BOTTOM_MID, DOOR_BOTTOM_LEFT, DOOR_BOTTOM_RIGHT,
	CASTLE_BOTTOM_RIGHT,

	STATUE_SPIRAL_LEFT = 70, STATUE_SPIRAL_RIGHT, PILLAR, STATUE_BOTTOM_LEFT, STATUE_BOTTOM_RIGHT, STATUE_TOP_LEFT, STATUE_TOP_RIGHT,

	//2nd stage
	WALL = 81, ARCH_LEFT, ARCH_MID_LEFT, ARCH_MID_RIGHT, ARCH_RIGHT, COLUMN_LEFT, COLUMN_RIGHT, BROKEN_MID, BROKEN_RIGHT, BROKEN_LEFT/*90*/, BROKEN_PEAK, BROKEN_BOTTOM_LEFT,
	BROKEN_BOTTOM_RIGHT,BROKEN_CRUMBS_LEFT, BROKEN_CRUMBS_RIGHT, NARROW_WINDOW_LEFT_TOP, NARROW_WINDOW_RIGHT_TOP, NARROW_WINDOW_LEFT_BOTTOM, NARROW_WINDOW_RIGHT_BOTTOM, BROKEN_BLACK_LEFT/*100*/,
	BROKEN_BLACK_RIGHT,COLOR_WINDOW_TOP_LEFT, COLOR_WINDOW_TOP_RIGHT,COLOR_WINDOW_BOTTOM_LEFT, COLOR_WINDOW_BOTTOM_RIGHT,

//GADGETS
    STAIRS = 110, PINK_DOOR_TOP, PINK_DOOR_MID, PINK_DOOR_BOTTOM, CRUSHER_TOP, CRUSHER_MID, CRUSHER_BOTTOM, CRUSHER_PLATAFORM_MID, CRUSHER_PLATAFOR_LEFT, CRUSHER_PLATAFORM_RIGHT, 

//ENTITY

PLAYER = 400, 
SOLDIER = 150, HEAD, MEDUSA_BOTTOM_LEFT, MEDUSA_BOTTOM_RIGHT, MEDUSA_MID_LEFT, MEDUSA_MID_RIGHT, MEDUSA_TOP_LEFT, MEDUSA_TOP_RIGHT,



//OBJECT 
    ITEM_HEART = 200, FIRE, FIRE_FRAME0, FIRE_FRAME1, ITEM_RING,

//EXTRA TILES
    FENCE_TOP3 = 250, TREE_HANG_LEAF5, TREE_HANG_LEAF6, BROKEN_CASTLE, 

 //TRANSITION TILES
	CASTLE_LAB1 = 300, LAB1_LAB2, LAB2_LAB3, LAB3_LAB1, 
	                   LAB2_LAB1, LAB3_LAB2, LAB1_LAB3,
					   GARDEN1_GARDEN2, GARDEN2_GARDEN3,
					   GARDEN2_GARDEN1, GARDEN3_GARDEN2,

//INTERVALS
    SOLID_FIRST = CLAY_GROUND,
	SOLID_LAST = GROUND,
    SPECIAL_FIRST = FIRE,
	SPECIAL_LAST = FIRE,
	



};

class TileMap
{
public:
	TileMap();
	~TileMap();

	AppStatus Initialise();
	AppStatus Load(int data[], int w, int h);
	void Update();
	void Render();
	void Release();

	//Test for collisions with walls
	bool TestCollisionWallLeft(const AABB& box) const;
	bool TestCollisionWallRight(const AABB& box) const;

	//Test collision with the ground and update 'py' with the maximum y-position to prevent
	//penetration of the grounded tile, that is, the pixel y-position above the grounded tile.
	//Grounded tile = solid tile (blocks) or ladder tops.
	bool TestCollisionGround(const AABB& box, int* py) const;
	/*int TestTransition(const AABB& box) const;*/

	//Test if there is a ground tile one pixel below the given box
	bool TestFalling(const AABB& box) const;


private:
	void InitTileDictionary();

	Tile GetTileIndex(int x, int y) const;
	bool IsTileSolid(Tile tile) const;
	bool CollisionX(const Point& p, int distance) const;
	bool CollisionY(const Point& p, int distance) const;

	//Tile map
	Tile* map;

	//Size of the tile map
	int size, width, height;

	//Dictionary of tile frames
	std::unordered_map<int, Rectangle> dict_rect;

	Sprite* fire;

	//Tile sheet
	const Texture2D* img_tiles;
	const Texture2D* img_items;
};

