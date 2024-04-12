#pragma once
#include <raylib.h>
#include "Sprite.h"
#include "Globals.h"
#include <unordered_map>

enum class Tile
{
	//empty tile
	AIR = 0,

	//ground/wall tiles



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