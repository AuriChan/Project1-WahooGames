#pragma once
#include <raylib.h>
#include "Sprite.h"
#include "Globals.h"
#include <unordered_map>

enum class Tile
{
	//empty tile
	AIR = 0,

    //1ST SCENE
	GROUND, FENCE_BOTTOM, FENCE_TOP1, FECNCE_TOP2,
	TREE_LOG_RIGHT = 10,TREE_HANG_LEAF1, TREE_LOG_LEFT, TREE_HANG_LEAF2, TREE_HANG_LEAF3, TREE_HANG_LEAF4, LEAFS_BOTTOM1, LEAFS_BOTTOM2, LEAFS_BOTTOM3, LEAFS_BOTTOM4, LEAFS_BOTTOM5, LEAFS_BOTTOM6,
	LEAFS_TOP1, LEAFS_TOP_TREE1, LEAFS_TOP2, LEAFS_TOP3, LEAFS_TOP4, LEAFS_TOP5, LEAFS_TOP6, LEAFS_TOP7, LEAFS_TOP8, LEAFS_TOP_TREE2, LEAFS_TOP_TREE3, LEAFS_TOP9, LEAFS_TOP_TREE4, LEAFS_TOP_TREE5,
	LEAFS_TOP10, LEAFS_TOP11, LEAFS_TOP_SKY1, LEAFS_TOP_SKY2, LEAFS_TOP_SKY3, LEAFS_TOP_SKY4, LEAFS_TOP_SKY_CASTLE, TOP_CASTLE1, TOP_CASTLE2, MID_CASTLE1, MID_CASTLE2,BROKEN_CASTLE_LEFT, BROKEN_CASTLE_RIGHT,
	MID_CASTLE3, MID_CASTLE4, TOP_WINDOW_LEFT, DOOR_TOP_LEFT, DOOR_TOP_RIGHT, TOP_WINDOW_RIGHT,

	



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

private:
	void InitTileDictionary();

	//Tile map
	Tile* map;

	//Size of the tile map
	int width, height;
	//Map is rendered from this position (margin for GUI) 
	int map_y;

	//Dictionary of tile frames
	std::unordered_map<int, Rectangle> dict_rect;

	//Tile sheet
	Texture2D img_tiles;
};