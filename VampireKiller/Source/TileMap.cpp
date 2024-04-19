#include "TileMap.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <cstring>

TileMap::TileMap()
{
	map = nullptr;
	width = 0;
	height = 0;
	/*fire = nullptr;*/
	img_tiles = nullptr;
	img_items = nullptr;

	InitTileDictionary();
}
TileMap::~TileMap()
{
	if (map != nullptr)
	{
		delete[] map;
		map = nullptr;
	}
	/*if (fire != nullptr)
	{
		fire->Release();
		delete fire;
		fire = nullptr;
	}*/
}

void TileMap::InitTileDictionary()
{
	const int n = TILE_SIZE;

//BACKGROUND
	
	//empty
	
	//stage1
	dict_rect[(int)Tile::SOLID_LAST] = { 0,  0, n, n };
	dict_rect[(int)Tile::FENCE_BOTTOM] = { 1 * n, 0 * n, n, n };
	dict_rect[(int)Tile::FENCE_TOP1] = { 2 * n, 0 * n, n, n };
	dict_rect[(int)Tile::FECNCE_TOP2] = { 3 * n, 0 * n, n, n };
	dict_rect[(int)Tile::TREE_LOG_RIGHT] = { 4 * n, 0 * n, n, n };
	dict_rect[(int)Tile::TREE_HANG_LEAF1] = { 5 * n, 0 * n, n, n };
	dict_rect[(int)Tile::TREE_LOG_LEFT] = { 6 * n, 0 * n, n, n };
	dict_rect[(int)Tile::TREE_HANG_LEAF2] = { 7 * n, 0 * n, n, n };
	dict_rect[(int)Tile::TREE_HANG_LEAF3] = { 8 * n, 0 * n, n, n };
	dict_rect[(int)Tile::TREE_HANG_LEAF4] = { 9 * n, 0 * n, n, n };
	dict_rect[(int)Tile::LEAFS_BOTTOM1] = { 10 * n, 0 * n, n, n };
	dict_rect[(int)Tile::LEAFS_BOTTOM2] = { 11 * n, 0 * n, n, n };
	dict_rect[(int)Tile::LEAFS_BOTTOM3] = { 12 * n, 0 * n, n, n };
	dict_rect[(int)Tile::LEAFS_BOTTOM4] = { 13 * n, 0 * n, n, n };
	dict_rect[(int)Tile::LEAFS_BOTTOM5] = { 14 * n, 0 * n, n, n };
	dict_rect[(int)Tile::LEAFS_BOTTOM6] = { 15 * n, 0 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP1] = { 0 * n, 1 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP_TREE1] = { 1 * n, 1 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP2] = { 2 * n, 1 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP3] = { 3 * n, 1 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP4] = { 4 * n, 1 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP5] = { 5 * n, 1 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP6] = { 6 * n, 1 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP7] = { 7 * n, 1 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP8] = { 8 * n, 1 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP_TREE2] = { 9 * n, 1 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP_TREE3] = { 10 * n, 1 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP9] = { 11 * n, 1 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP_TREE4] = { 12 * n, 1 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP_TREE5] = { 13 * n, 1 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP10] = { 14 * n, 1 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP11] = { 15 * n, 1 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP_SKY1] = { 0 * n, 2 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP_SKY2] = { 1 * n, 2 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP_SKY3] = { 2 * n, 2 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP_SKY4] = { 3 * n, 2 * n, n, n };
	dict_rect[(int)Tile::LEAFS_TOP_SKY_CASTLE] = { 4 * n, 2 * n, n, n };
	dict_rect[(int)Tile::TOP_CASTLE1] = { 5 * n, 2 * n, n, n };
	dict_rect[(int)Tile::TOP_CASTLE2] = { 6 * n, 2 * n, n, n };
	dict_rect[(int)Tile::MID_CASTLE1] = { 7 * n, 2 * n, n, n };
	dict_rect[(int)Tile::MID_CASTLE2] = { 8 * n, 2 * n, n, n };
	dict_rect[(int)Tile::BROKEN_CASTLE_LEFT] = { 9 * n, 2 * n, n, n };
	dict_rect[(int)Tile::BROKEN_CASTLE_RIGHT] = { 10 * n, 2 * n, n, n };
	dict_rect[(int)Tile::MID_CASTLE3] = { 11 * n, 2 * n, n, n };
	dict_rect[(int)Tile::MID_CASTLE4] = { 12 * n, 2 * n, n, n };
	dict_rect[(int)Tile::TOP_WINDOW_LEFT] = { 13 * n, 2 * n, n, n };
	dict_rect[(int)Tile::DOOR_TOP_LEFT] = { 14 * n, 2 * n, n, n };
	dict_rect[(int)Tile::DOOR_TOP_RIGHT] = { 15 * n, 2 * n, n, n };
	dict_rect[(int)Tile::TOP_WINDOW_RIGHT] = { 0 * n, 3 * n, n, n };
	dict_rect[(int)Tile::MID_CASTLE5] = { 1 * n, 3 * n, n, n };
	dict_rect[(int)Tile::DOOR_LEFT_BROKEN] = { 2 * n, 3 * n, n, n };
	dict_rect[(int)Tile::DOOR_RIGHT] = { 3 * n, 3 * n, n, n };
	dict_rect[(int)Tile::WINDOW_BOTTOM_LEFT] = { 4 * n, 3 * n, n, n };
	dict_rect[(int)Tile::DOOR_LEFT] = { 5 * n, 3 * n, n, n };
	dict_rect[(int)Tile::DOOR_RIGHT_BROKEN] = { 6 * n, 3 * n, n, n };
	dict_rect[(int)Tile::WINDOW_BOTTOM_RIGHT] = { 7 * n, 3 * n, n, n };
	dict_rect[(int)Tile::CASTLE_BOTTOM_LEFT] = { 8 * n, 3 * n, n, n };
	dict_rect[(int)Tile::CASTLE_BOTTOM_MID] = { 9 * n, 3 * n, n, n };
	dict_rect[(int)Tile::DOOR_BOTTOM_LEFT] = { 10 * n, 3 * n, n, n };
	dict_rect[(int)Tile::DOOR_BOTTOM_RIGHT] = { 11 * n, 3 * n, n, n };
	dict_rect[(int)Tile::CASTLE_BOTTOM_RIGHT] = { 12 * n, 3 * n, n, n };
	dict_rect[(int)Tile::STATUE_SPIRAL_LEFT] = { 13 * n, 3 * n, n, n };
	dict_rect[(int)Tile::STATUE_SPIRAL_RIGHT] = { 14 * n, 3 * n, n, n };
	dict_rect[(int)Tile::PILLAR] = { 15 * n, 3 * n, n, n };
	dict_rect[(int)Tile::STATUE_BOTTOM_LEFT] = { 0 * n, 4 * n, n, n };
	dict_rect[(int)Tile::STATUE_BOTTOM_RIGHT] = { 1 * n, 4 * n, n, n };
	dict_rect[(int)Tile::STATUE_TOP_LEFT] = { 2 * n, 4 * n, n, n };
	dict_rect[(int)Tile::STATUE_TOP_RIGHT] = { 3 * n, 4 * n, n, n };
	//stage2
	dict_rect[(int)Tile::SOLID_FIRST] = { 4 * n, 4 * n, n, n };
	dict_rect[(int)Tile::WALL] = { 5 * n, 4 * n, n, n };
	dict_rect[(int)Tile::ARCH_LEFT] = {6 *n, 4 * n, n, n };
	dict_rect[(int)Tile::ARCH_MID_LEFT] = { 7*n, 4 * n, n, n };
	dict_rect[(int)Tile::ARCH_MID_RIGHT] = { 8*n, 4 * n, n, n };
	dict_rect[(int)Tile::ARCH_RIGHT] = { 9*n, 4 * n, n, n };
	dict_rect[(int)Tile::COLUMN_LEFT] = {10 *n, 4 * n, n, n };
	dict_rect[(int)Tile::COLUMN_RIGHT] = { 11 *n, 4 * n, n, n };
	dict_rect[(int)Tile::BROKEN_MID] = { 13*n, 4 * n, n, n };
	dict_rect[(int)Tile::BROKEN_RIGHT] = { 14*n, 4 * n, n, n };
	dict_rect[(int)Tile::BROKEN_LEFT] = { 15 * n, 4 * n, n, n };
	dict_rect[(int)Tile::BROKEN_PEAK] = { 0 * n, 5 * n, n, n };
	dict_rect[(int)Tile::BROKEN_BOTTOM_LEFT] = { 1 *n, 5 * n, n, n };
	dict_rect[(int)Tile::BROKEN_BOTTOM_RIGHT] = { 2 *n, 5 * n, n, n };
	dict_rect[(int)Tile::BROKEN_CRUMBS_LEFT] = { 3 *n, 5 * n, n, n };
	dict_rect[(int)Tile::BROKEN_CRUMBS_RIGHT] = { 4 * n, 5 * n, n, n };
	dict_rect[(int)Tile::STAIRS] = { 5*n, 5 * n, n, n };
	dict_rect[(int)Tile::NARROW_WINDOW_LEFT_TOP] = { 6 *n, 5 * n, n, n };
	dict_rect[(int)Tile::NARROW_WINDOW_RIGHT_TOP] = {7 *n, 5 * n, n, n };
	dict_rect[(int)Tile::NARROW_WINDOW_LEFT_BOTTOM] = { 8*n, 5 * n, n, n };
	dict_rect[(int)Tile::NARROW_WINDOW_RIGHT_BOTTOM] = { 9 *n, 5 * n, n, n };
	dict_rect[(int)Tile::BROKEN_BLACK_LEFT] = {10 *n, 5 * n, n, n };
	dict_rect[(int)Tile::BROKEN_BLACK_RIGHT] = { 11 *n, 5 * n, n, n };
	dict_rect[(int)Tile::COLOR_WINDOW_TOP_LEFT] = { 12 *n, 5 * n, n, n };
	dict_rect[(int)Tile::COLOR_WINDOW_TOP_RIGHT] = { 13*n, 5 * n, n, n };
	dict_rect[(int)Tile::COLOR_WINDOW_BOTTOM_LEFT] = { 14*n, 5 * n, n, n };
	dict_rect[(int)Tile::COLOR_WINDOW_BOTTOM_RIGHT] = { 15 *n, 5 * n, n, n };

//ENTITIES

	//dict_rect[(int)Tile::PLAYER] = { 0 * n, 0 * n, n, n };
	dict_rect[(int)Tile::MEDUSA_BOTTOM_LEFT] = { 0 *n, 6 * n, n, n };
	dict_rect[(int)Tile::MEDUSA_BOTTOM_RIGHT] = { 1 *n, 6 * n, n, n };
	dict_rect[(int)Tile::MEDUSA_MID_LEFT] = { 2*n, 6 * n, n, n };
	dict_rect[(int)Tile::MEDUSA_MID_RIGHT] = { 3*n, 6 * n, n, n };
	dict_rect[(int)Tile::MEDUSA_TOP_LEFT] = { 4 *n, 6 * n, n, n };
	dict_rect[(int)Tile::MEDUSA_TOP_RIGHT] = { 5*n, 6 * n, n, n };
	//dict_rect[(int)Tile::SOLDIER] = { 12 * n, 4 * n, n, n };
	dict_rect[(int)Tile::HEAD] = { 9 * n, 2 * n, n, n };

//GADGETS
	
	//stage1
	dict_rect[(int)Tile::FIRE_FRAME0] = { 5 * n,  3* n, n, n };
	dict_rect[(int)Tile::FIRE_FRAME1] = { 6 * n,  3* n, n, n };

    //stage2
	dict_rect[(int)Tile::PINK_DOOR_TOP] = { 6 * n, 6 * n, n, n };
	dict_rect[(int)Tile::PINK_DOOR_MID] = { 6 * n, 7 * n, n, n };
	dict_rect[(int)Tile::PINK_DOOR_BOTTOM] = { 6 * n, 8 * n, n, n };
	dict_rect[(int)Tile::CRUSHER_TOP] = { 7 * n, 6 * n, n, n };
	dict_rect[(int)Tile::CRUSHER_MID] = { 7 * n, 7 * n, n, n };
	dict_rect[(int)Tile::CRUSHER_BOTTOM] = { 7 * n, 8 * n, n, n };
	dict_rect[(int)Tile::CRUSHER_PLATAFORM_MID] = { 7 * n, 9 * n, n, n };
	dict_rect[(int)Tile::CRUSHER_PLATAFOR_LEFT] = { 6 * n, 9 * n, n, n };
	dict_rect[(int)Tile::CRUSHER_PLATAFORM_RIGHT] = { 8 * n, 9 * n, n, n };

//OBJECTS
	/*dict_rect[(int)Tile::ITEM_HEART] ={ 7 * n, 1 * n, n, n } ;*/
	
//EXTRA TILES 
	dict_rect[(int)Tile::FENCE_TOP3] = { 0 * n, 7 * n, n, n };
	dict_rect[(int)Tile::TREE_HANG_LEAF5] = { 1 * n, 7 * n, n, n };
	dict_rect[(int)Tile::TREE_HANG_LEAF6] = { 2 * n, 7 * n, n, n };
	dict_rect[(int)Tile::BROKEN_CASTLE] = { 3 * n, 7 * n, n, n };

//TRANSITION TILES
	dict_rect[(int)Tile::CASTLE_LAB1] = { 12 * n, 4 * n, n, n };
	dict_rect[(int)Tile::LAB1_LAB2] = { 5 * n, 4 * n, n, n };
	dict_rect[(int)Tile::LAB2_LAB3] = { 11 * n, 4 * n, n, n };
	dict_rect[(int)Tile::LAB3_LAB1] = {  9* n, 5 * n, n, n };
	dict_rect[(int)Tile::LAB2_LAB1] = { 8 * n, 5 * n, n, n };
	dict_rect[(int)Tile::LAB3_LAB2] = { 5 * n, 4 * n, n, n };
	dict_rect[(int)Tile::LAB1_LAB3] = { 3 * n, 5 * n, n, n };

	dict_rect[(int)Tile::GARDEN1_GARDEN2] = { 0 * n, 7 * n, n, n };
	dict_rect[(int)Tile::GARDEN2_GARDEN3] = { 0 * n, 7 * n, n, n };
	dict_rect[(int)Tile::GARDEN2_GARDEN1] = { 1 * n, 0 * n, n, n };
	dict_rect[(int)Tile::GARDEN3_GARDEN2] = { 1 * n, 0 * n, n, n };

}


AppStatus TileMap::Initialise()
{
	ResourceManager& data = ResourceManager::Instance();

	if (data.LoadTexture(Resource::IMG_TILES, "Images/Tileset.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}
	img_tiles = data.GetTexture(Resource::IMG_TILES);

	if (data.LoadTexture(Resource::IMG_ITEMS, "Images/objects.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}
	img_items = data.GetTexture(Resource::IMG_ITEMS);

	/*fire = new Sprite(img_items);
	if (fire == nullptr)
	{
		LOG("Failed to allocate memory for fire sprite");
		return AppStatus::ERROR;
	}
	fire->SetNumberAnimations(1);
	fire->SetAnimationDelay(0, ANIM_DELAY);
	fire->AddKeyFrame(0, dict_rect[(int)Tile::FIRE_FRAME0]);
	fire->AddKeyFrame(0, dict_rect[(int)Tile::FIRE_FRAME1]);
	fire->SetAnimation(0);*/

	return AppStatus::OK;
}
AppStatus TileMap::Load(int data[], int w, int h)
{
	size = w * h;
	width = w;
	height = h;

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
	/*fire->Update();*/
}
Tile TileMap::GetTileIndex(int x, int y) const
{
	int idx = x + y * width;
	if (idx < 0 || idx >= size)
	{
		LOG("Error: Index out of bounds. Tile map dimensions: %dx%d. Given index: (%d, %d)", width, height, x, y)
			return Tile::AIR;
	}
	return map[x + y * width];
}
bool TileMap::IsTileSolid(Tile tile) const
{
	return (Tile::SOLID_FIRST <= tile && tile <= Tile::SOLID_LAST);
}
//bool TileMap::IsTileLadderTop(Tile tile) const
//{
//	return tile == Tile::LADDER_TOP_L || tile == Tile::LADDER_TOP_R;
//}
//bool TileMap::IsTileLadder(Tile tile) const
//{
//	return tile == Tile::LADDER_L || tile == Tile::LADDER_R;
//}
bool TileMap::TestCollisionWallLeft(const AABB& box) const
{
	return CollisionX(box.pos, box.height);
}
bool TileMap::TestCollisionWallRight(const AABB& box) const
{
	return CollisionX(box.pos + Point(box.width - 1, 0), box.height);
}
bool TileMap::TestCollisionGround(const AABB& box, int* py) const
{
	Point p(box.pos.x, *py);	//control point
	int tile_y;

	if (CollisionY(p, box.width))
	{
		tile_y = p.y / TILE_SIZE;
		
		*py = tile_y * TILE_SIZE - 1;
		return true;
	}
	return false;
}
//int TileMap::TestTransition(const AABB& box) const 
//{
//	Tile t = GetTileIndex(box.pos.x, box.pos.y);
//	if (t == Tile::LAB1_LAB2)
//	{
//		return 1;
//	}
//
//	return 0;
//}

bool TileMap::TestFalling(const AABB& box) const
{
	return !CollisionY(box.pos + Point(0, box.height), box.width);
}
bool TileMap::CollisionX(const Point& p, int distance) const
{
	int x, y, y0, y1;

	//Calculate the tile coordinates and the range of tiles to check for collision
	x = p.x / TILE_SIZE;
	y0 = p.y / TILE_SIZE;
	y1 = (p.y + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the vertical range
	for (y = y0; y <= y1; ++y)
	{
		//One solid tile is sufficient
		if (IsTileSolid(GetTileIndex(x, y)))
			return true;
	}
	return false;
}
bool TileMap::CollisionY(const Point& p, int distance) const
{
	int x, y, x0, x1;
	Tile tile;

	//Calculate the tile coordinates and the range of tiles to check for collision
	y = p.y / TILE_SIZE;
	x0 = p.x / TILE_SIZE;
	x1 = (p.x + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the horizontal range
	for (x = x0; x <= x1; ++x)
	{
		tile = GetTileIndex(x, y);

		//One solid or laddertop tile is sufficient
		if (IsTileSolid(tile)) //|| IsTileLadderTop(tile))
			return true;
	}
	return false;
}
//bool TileMap::TestOnLadder(const AABB& box, int* px) const
//{
//	int left, right, bottom;
//	int tx1, tx2, ty;
//	Tile tile1, tile2;
//
//	//Control points
//	left = box.pos.x;
//	right = box.pos.x + box.width - 1;
//	bottom = box.pos.y + box.height - 1;
//
//	//Calculate the tile coordinates
//	tx1 = left / TILE_SIZE;
//	tx2 = right / TILE_SIZE;
//	ty = bottom / TILE_SIZE;
//
//	//To be able to climb up or down, both control points must be on ladder
//	tile1 = GetTileIndex(tx1, ty);
//	tile2 = GetTileIndex(tx2, ty);
//	if (IsTileLadder(tile1) && IsTileLadder(tile2))
//	{
//		*px = GetLadderCenterPos(left, bottom) - box.width / 2;
//		return true;
//	}
//	return false;
//}
//bool TileMap::TestOnLadderTop(const AABB& box, int* px) const
//{
//	int left, right, bottom;
//	int tx1, tx2, ty;
//	Tile tile1, tile2;
//
//	//Control points
//	left = box.pos.x;
//	right = box.pos.x + box.width - 1;
//	bottom = box.pos.y + box.height - 1;
//
//	//Calculate the tile coordinates
//	tx1 = left / TILE_SIZE;
//	tx2 = right / TILE_SIZE;
//	ty = bottom / TILE_SIZE;
//
//	//To be able to climb up or down, both control points must be on ladder
//	tile1 = GetTileIndex(tx1, ty);
//	tile2 = GetTileIndex(tx2, ty);
//	if (IsTileLadderTop(tile1) && IsTileLadderTop(tile2))
//	{
//		*px = GetLadderCenterPos(left, bottom) - box.width / 2;
//		return true;
//	}
//	return false;
//}
//int TileMap::GetLadderCenterPos(int pixel_x, int pixel_y) const
//{
//	int tx, ty;
//
//	tx = pixel_x / TILE_SIZE;
//	ty = pixel_y / TILE_SIZE;
//	Tile tile = GetTileIndex(tx, ty);
//
//	if (tile == Tile::LADDER_L || tile == Tile::LADDER_TOP_L)		return tx * TILE_SIZE + TILE_SIZE;
//	else if (tile == Tile::LADDER_R || tile == Tile::LADDER_TOP_R)	return tx * TILE_SIZE;
//	else
//	{
//		LOG("Internal error, tile should be a LADDER, coord: (%d,%d), tile type: %d", pixel_x, pixel_y, (int)tile);
//		return 0;
//	}
//}
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
				pos.x = (float)j * TILE_SIZE;
				pos.y = (float)i * TILE_SIZE;

				if (tile != Tile::FIRE)
				{
					rc = dict_rect[(int)tile];
					DrawTextureRec(*img_tiles, rc, pos, WHITE);
				}
				/*else
				{
					fire->Draw((int)pos.x, (int)pos.y);
				}*/
			}
		}
	}
}

void TileMap::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_TILES);
	data.ReleaseTexture(Resource::IMG_ITEMS);

	/*fire->Release();*/

	dict_rect.clear();
}