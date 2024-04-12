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
	dict_rect[(int)Tile::GROUND] = { 0,  0, n, n };

}

AppStatus TileMap::Initialise()
{
	img_tiles = LoadTexture("Images/Tileset.png");
	if (img_tiles.id == 0)
	{
		LOG("Failed to load texture images/tileset.png");
		return AppStatus::ERROR;
	}
	return AppStatus::OK;
}

AppStatus TileMap::Load(int data[], int w, int h)
{
	int size = w * h;

	width = w;
	height = h;
	map_y = WINDOW_HEIGHT - h * TILE_SIZE;

	if (map != nullptr)	delete[] map;

	map = new Tile[size];
	if (map == nullptr)
	{
		LOG("Failed to allocate memory for tile map");
		return AppStatus::ERROR;
	}
	memcpy(map, data, size * sizeof(int));

	return AppStatus::OK;
}
void TileMap::Update()
{
}
void TileMap::Render()
{
	Tile tile;
	Rectangle rc;
	Vector2 pos;

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			tile = map[i * width + j];
			if (tile != Tile::AIR)
			{
				pos.x = j * TILE_SIZE;
				pos.y = map_y + i * TILE_SIZE;

				rc = dict_rect[(int)tile];
				DrawTextureRec(img_tiles, rc, pos, WHITE);
			}
		}
	}
}
void TileMap::Release()
{
	UnloadTexture(img_tiles);
	dict_rect.clear();
}