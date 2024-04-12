#include "TileMap.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <cstring>

TileMap::TileMap()
{
	map = nullptr;
	width = 0;
	height = 0;
	map_y = 0;
	img_tiles = {};

	InitTileDictionary();
}

TileMap::~TileMap()
{
	if (map != nullptr)
	{
		delete[] map;
		map = nullptr;
	}
}

void TileMap::InitTileDictionary()
{
	const int n = TILE_SIZE;

}

AppStatus TileMap::Initialise()
{
	img_tiles = LoadTexture("Images/Tileset_Stage_2.png");
	if (img_tiles.id == 0)
	{
		LOG("Failed to load texture images/tileset.png");
		return AppStatus::ERROR;
	}
	return AppStatus::OK;
}