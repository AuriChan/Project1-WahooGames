#include "Scene.h"
#include "Globals.h"
#include <stdio.h>
#include "TileMap.h"
Player* Scene::GetPlayer()const
{
	return player;
}

Music Scene::GetMusic(int i) const
{
	return musics[i];
}
Scene::Scene()
{
	player = nullptr;

	level = nullptr;
	

	camera.target = { 0, 0 };				//Center of the screen
	camera.offset = { 0, MARGIN_GUI_Y };	//Offset from the target (center of the screen)
	camera.rotation = 0.0f;					//No rotation
	camera.zoom = 1.0f;						//Default zoom

	debug = DebugMode::OFF;

	
	
	musics[0] = LoadMusicStream("Images/VampireKiller.mp3");
	musics[1] = LoadMusicStream("Images/Starker.mp3");
	musics[2] = LoadMusicStream("Images/Ending.mp3");
	musics[3] = LoadMusicStream("Images/Prologue.mp3");
	musics[4] = LoadMusicStream("Images/GameOver.mp3");
	musics[0].looping = true;
	musics[1].looping = true;
	musics[2].looping = true;
	musics[3].looping = true;
	musics[4].looping = false;
	PlayMusicStream(musics[0]);
	PlayMusicStream(musics[1]);
	PlayMusicStream(musics[2]);
	PlayMusicStream(musics[3]);
	PlayMusicStream(musics[4]);
	
}
Scene::~Scene()
{
	if (player != nullptr)
	{
		player->Release();
		delete player;
		player = nullptr;
	}
	

	if (level != nullptr)
	{
		level->Release();
		delete level;
		level = nullptr;
	}
	for (Entity* obj : objects)
	{
		delete obj;
	}
	objects.clear();
	for (Entity* obj : objects2)
	{
		delete obj;
	}
	objects2.clear();
}
AppStatus Scene::Init()
{
	//Create player
	player = new Player({ 0,0 }, State::IDLE, Look::RIGHT);
	if (player == nullptr)
	{
		LOG("Failed to allocate memory for Player");
		return AppStatus::ERROR;
	}
	//Initialise player
	if (player->Initialise() != AppStatus::OK)
	{
		LOG("Failed to initialise Player");
		return AppStatus::ERROR;
	}
	//Create enemy
	
	//Initialise player
	

	//init fire
	 
	//Create level 
	level = new TileMap();
	if (level == nullptr)
	{
		LOG("Failed to allocate memory for Level");
		return AppStatus::ERROR;
	}
	//Initialise level
	if (level->Initialise() != AppStatus::OK)
	{
		LOG("Failed to initialise Level");
		return AppStatus::ERROR;
	}

	//Load level
	if (LoadLevel(1) != AppStatus::OK)
	{
		LOG("Failed to load Level 1");
		return AppStatus::ERROR;
	}
	//Assign the tile map reference to the player to check collisions while navigating
	player->SetTileMap(level);
	
	

	return AppStatus::OK;
}
AppStatus Scene::LoadLevel(int stage)
{
	int size;
	int x, y, i;
	Tile tile;
	Tile tile2;
	Point pos;
	int* map = nullptr;
	int* map2 = nullptr;
	Object* obj;
	
	

	ClearLevel();

	size = LEVEL_WIDTH * LEVEL_HEIGHT;
	if (stage == 1)
	{
		map = new int[size] {
					
					38,  39,  40,  41,  38,  39,  40,  41,  38,  39,  40,  41,  38,  39,  40,  41,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
					34,  35,  36,  37,  34,  35,  36,  37,  34,  35,  36,  37,  34,  35,  36,  37,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
					30,  31,  32,  33,  30,  31,  32,  33,  30,  31,  32,  33,  30,  31,  32,  33,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
					26,  27,  28,  29,  26,  27,  28,  29,  26,  27,  28,  29,  26,  27,  28,  29,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
					22,  23,  24,  25,  22,  23,  24,  25,  22,  23,  24,  25,  22,  23,  24,  25,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
					18,  16,  15,  14,  17,  19,  18,  21,  18,  19,  20,  21,  17,  19,  20,  21,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
					10,  11,  75,  76,   0,  12,  10,  12,  10,  12,  10, 251,   0,  12,  10,  12,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
					 3, 250,  73,  74, 201, 250,   4, 250,   4, 250,   4, 250, 201, 250,   3, 307,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
					 2,   2,  70,  71, 72,   2,   2,   2,   2,   2,   2,   2,  72,   2,   2,   2,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
					-2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,   1,   1,   1,   1,   1,   1,   1,   1,   1,
					 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
			};
		map2 = new int[size] {
					
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					   400, 0,0, 0, 0, 0,  0, 0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
			};
		player->InitScore();
		player->SetStage(1);
		
		
		
	}
	else if (stage == 2)
	{
		map = new int[size] {
			 
			
			38,  39,  40,  41,  38,  39,  40,  41,  38,  39,  40,  41,  38,  39,  40,  41,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
			34,  35,  36,  37,  34,  35,  36,  37,  34,  35,  36,  37,  34,  35,  36,  37,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
			30,  31,  32,  33,  30,  31,  32,  33,  30,  31,  32,  33,  30,  31,  32,  33,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
			26,  27,  28,  29,  26,  27,  28,  29,  26,  27,  28,  29,  26,  27,  28,  29,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
			22,  23,  24,  25,  22,  23,  24,  25,  22,  23,  24,  25,  22,  23,  24,  25,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
			18,  16,  15,  14,  17,  19,  18,  21,  18,  19,  20,  21,  17,  19,  20,  21,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
			10,  11,  75,  76,   0,  12,  10,  12,  10,  12,  10, 251,   0,  12,  10,  12,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
			 3, 250,  73,  74, 201, 250,   4, 250,   4, 250,   4, 250, 201, 250,   3, 308,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
		   309,   2,  70,  71,  72,   2,   2,   2,   2,   2,   2,   2,  72,   2,   2,   2,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
		    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
			};
		map2 = new int[size] {
			
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			};
		player->SetStage(2);
	
	}
	else if (stage == 3)
	{
		map = new int[size] {
			
							38,  39,  40,  41,  38,  39,  40,  41,  38,  39,  42,  43,  44,  43,  44,  43,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							34,  35,  36,  37,  34,  35,  36,  37,  34,  35,  50,  46,  47,  48,  48, 253,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							30,  31,  32,  33,  30,  31,  32,  33,  30,  31,  50,  51,  52,   53, 48,  54,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							26,  27,  28,  29,  26,  27,  28,  29,  26,  27,  50,  55,  56,  300,  57, 253,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							22,  23,  24,  25,  22,  23,  24,  25,  22,  23,  50,  58,  59,  300,  60,  61,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							18,  16,  15,  14,  17,  19,  18,  21,  18,  19,  50,  55,  56,  300,  57, 253,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							10,  11,  75,  76,   0,  12,  10,  12,  10,  12,  50,  58,  59,  300,  60,  61,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							 3, 250,  73,  74, 201, 250,   4, 250,   4, 250,  62,  63,  64,  300,  65,  66,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
						   310,   2,  70,  71,  72,   2,   2,   2,   2,   2,  62,  63,  64,  300,  65,  66,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
							 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
			};
		map2 = new int[size] {
			
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			};
		player->SetStage(3);
		
	}
	else if (stage == 4)
	{
		map = new int[size] {
			
							-3,  -3,  -3,  -3,  81,  81,  86,  87,  88,  89,  81,  81,  86,  87,  -3,  -3,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							-3,  -3,  -3,  -3,  96,  97,  86,  87,  92,  93,  96,  97,  86,  87,  -3,  -3,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							-3,  -3,  -3,  -3,  98,  99,  86,  87,  81,  95,  98,  99,  86,  87,  -3,  -3,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							-3,  -3,  -3,  -3,  81,  81,  86,  87,  90,  91,  81,  81,  86,  87,  -3,  -3,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							-3,  -3,  -3,  -3, -3,  -3,  -3,  -3,  -3, -3,  81,  81,  -3,  -3,  -3,  -3,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							-3,  -3,  -3,  -3,  81,  81,  86,  87,  81,  81,  81,  81,  86,  87,  92,  93,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							-3,  -3,  -3,  -3,  81,  81,  86,  87,  81,  81,  81,  81,  86,  87,  94,  95,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							92,  93,  81,  81,  96,  97,  86,  87,  81,  81,  81,  81,  86,  87,  81, 301,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
						   306,  95,  81,  81,  98,  99,  86,  87,  81,  81,  -3,  -3,  86,  87,  81, 301,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							88,  89,  81,  81,  90,  91,  86,  87,  81,  81,  90,  91,  86,  87,  88,  89,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							-3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  80,  80,  80,  80,  80,  80,  80,  80,   80
			};
		map2 = new int[size] {
			
				
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				400, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			};
		player->SetStage(4);
		
	}
	else if (stage == 5)
	{
		map = new int[size] {
			
							-3,  -3,  86,  87, 100, 101,  81,  81, 110,  81,  -3,  -3,  81,  81,  86,  87,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							-3,  -3,  86,  87,  81,  81,  81, 110,  96,  97,  -3,  -3,  81,  81,  86,  87,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							-3,  -3,  86,  87,  81,  81, 110,  81,  98,  99,  -3,  -3,  81,  81,  86,  87,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							-3,  -3,  86,  87,  81, 110,  90,  91,  81,  81,  -3,  -3,  90,  91,  86,  87,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							-3,  -3,  -3,  -3,  -3,  -3,  -3,  -3, 110,  -3,  -3,  -3,  88,  89,  -3,  -3,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							92,  93,  86,  87,  81,  81,  81, 110,  81,  81,  -3,  -3,  88,  89,  86,  87,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							94,  95,  86,  87,  81,  81, 110,  81,  81,  81,  -3,  -3,  -3,  -3,  86,  87,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							96,  97,  86,  87,  81, 110,  90,  91,  96,  97,  -3,  -3,  92,  93,  86, 302,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
						   304,  99,  86,  87, 110,  81,  88,  89,  98,  99,  -3,  -3,  94,  95,  86, 302,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							90,  91,  86, 110,  81,  81,  88,  92,  90,  91,  -3,  -3,  81,  81,  86, 302,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							-3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, 80, 80, 80, 80, 80, 80, 80, 80, 80
			};
		map2 = new int[size] {
			
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 204, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			};
		player->SetStage(5);
		
	}
	else if (stage == 6)
	{
		map = new int[size] {
			
							88,  89,  81,  81, 110,  81, -3,  -3,  81,  81,  94,  95, 110,  81,  -3,  -3,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							92,  93,  81, 110,  81,  81,  -3,  -3,  96,  97,  81, 110,  81,  81,  -3,  -3,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							94,  95, 110,  81,  81,  81,  -3,  -3,  98,  99, 110,  81,  81,  81,  -3,  -3,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							81, 110,  90,  91,  81,  81,  -3,  -3,  81, 110,  81,  81,  81,  81,  -3,  -3,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							-3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  -3,  81,  81,  81,  81,  -3,  -3,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							92,  93,  81,  81,  86,  87,  92,  93,  81,  81,  81,  81,  88,  89,  -3,  -3,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
			     			94,  95,  81,  81,  86,  87,  94,  95,  81,  81, 110,  -3,  -3,  -3,  -3,  -3,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
						   305,  81,  81,  81,  86,  87,  81,  81,  81, 110,  90,  91,  81,  81,  96,  97,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
						   305,  81,  -3,  -3,  86,  87,  81,  81, 110,  81,  88,  89,  81,  81,  98, 303,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
						   305,  81,  90,  91,  86,  87,  81, 110,  81,  81,  88,  89,  81,  81,  90,  91,   0,   0,   0,   0,   0,	  0,   0,   0,   0,
							-3,  -3, -3, -3,-3, -3,-3, -3, -3, -3, -3, -3, -3, -3, -3, -3, 80, 80, 80, 80, 80, 80, 80, 80, 80
			};
		map2 = new int[size] {
			
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			};
		    player->SetStage(6);
			
		}

	else if (stage == 7)
	{
		map = new int[size] {

			   -3,  -3,   81,  81,  81,  81,  86,  87, 81,   81,   94,  95, 86,   87,   81,   81,    0, 0, 0, 0, 0, 0, 0, 0, 0,
				0,   0,   96,  97,  81,  81,  86,  87, 96,   97,   81,  81, 86,   87,   96,   97,    0, 0, 0, 0, 0, 0, 0, 0, 0,
				0,   0,   98,  99,  81,  81,  86,  87, 98,   99,   81,  81, 86,   87,   98,   99,    0, 0, 0, 0, 0, 0, 0, 0, 0,
				0,   0,   90,  91,  81,  81,  86,  87, 81,   81,   81,  81, 86,   87,   90,   91,    0, 0, 0, 0, 0, 0, 0, 0, 0,
			   -3,  -3,   88,  89,  81,  81,  -3,  -3, -3,   -3,   81,  81, -3,   -3,   -3,   -3,    0, 0, 0, 0, 0, 0, 0, 0, 0,
			   -3,  81,   88,  92,  81,  81,  81,  81, -3,   -3,   81,  81, 86,   87,   -3,   -3,    0, 0, 0, 0, 0, 0, 0, 0, 0,
			   -3,  81,   -3,  -3,  81,  81,  81,  81, -3,   -3,   81,  81, 86,   87,   -3,   -3,    0, 0, 0, 0, 0, 0, 0, 0, 0,
			   -3,  81,   92,  93,  81,  81,  81,  81, -3,   -3,  106, 107, 86,   87,   -3,   -3,    0, 0, 0, 0, 0, 0, 0, 0, 0,
			   -3,  81,   94,  95,  81,  81,  -3,  -3, -3,   -3,  100, 101, 86,   87,   -3,   -3,    0, 0, 0, 0, 0, 0, 0, 0, 0,
			   -3,  81,   90,  91,  81,  81,  92,  93, -3,   -3,   81,  81, 86,   87,   -3,   -3,    0, 0, 0, 0, 0, 0, 0, 0, 0,
			   -3,  -3,   -3,  -3,  81,  81,  94,  95, -3,   -3,   81,  81, 86,   87,   -3,   -3,    0, 0, 0, 0, 0, 0, 0, 0, 0,
			};
		map2 = new int[size] {

			    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0,200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			   -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			  400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			};
		player->SetStage(7);

		}
	else if (stage == 8)
	{
		map = new int[size] {

			    94,  95,  81,  81,  86,  87, 100, 101,  81,  81,  81,  81,  86,  87,  81,  81,   0,   0, 0, 0, 0, 0, 0, 0, 0,
				81,  81,  96,  97,  86,  87,  90,  91,  96,  97,  81,  81,  86,  87,  96,  97,   0,   0, 0, 0, 0, 0, 0, 0, 0,
				81,  81,  98,  99,  86,  87,  88,  89,  98,  99,  81,  81,  86,  87,  98,  99,   0,   0, 0, 0, 0, 0, 0, 0, 0,
				81,  81,  90,  91,  86,  87,  92,  93,  90,  91,  81,  81,  86,  87,  81,  81,   0,   0, 0, 0, 0, 0, 0, 0, 0,
				-3,  -3,  88,  89,  86,  87,  94,  95,  -3,  -3,  81,  81,  -3,  -3,  -3,  -3,   0,   0, 0, 0, 0, 0, 0, 0, 0,
				-3,  81,  88,  92,  86,  87,  81,  81,  81,  81,  90,  91,  81,  81,  -3,  -3,   0,   0, 0, 0, 0, 0, 0, 0, 0,
				-3,  81,  -3,  -3,  86,  87,  81,  81,  81,  81,  -3,  -3,  81,  81,  -3,  -3,   0,   0, 0, 0, 0, 0, 0, 0, 0,
				-3,  81,  92,  93,  86,  87,  90,  91,  96,  97, 106, 107,  81,  81,  -3,  -3,   0,   0, 0, 0, 0, 0, 0, 0, 0,
				-3,  81,  94,  95,  -3,  -3,  -3,  -3,  98,  99, 100, 101,  81,  81,  -3,  -3,   0,   0, 0, 0, 0, 0, 0, 0, 0,
			    -3,  81,  81,  81,  86,  87,  92,  93,  81,  81,  81,  81,  92,  93,  -3,  -3,   0,   0, 0, 0, 0, 0, 0, 0, 0,
			    -3,  81,  81,  81,  86,  87,  94,  95, 110,  -3,  -3,  -3,  94,  95,  -3,  -3,   0,   0, 0, 0, 0, 0, 0, 0, 0,
			};
		map2 = new int[size] {

			    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			};
		player->SetStage(8);

		}
	else if (stage == 9)
	{
		map = new int[size] {

			    88,  89,  86,  87,  81,  81,  94,  95,  81,  81,  86,  87,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0,
			   106, 107,  86,  87,  96,  97,  81,  81,  96,  97,  86,  87,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0,
			   100, 101,  86,  87,  98,  99,  81,  81,  98,  99,  86,  87,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0,
				81,  81,  86,  87,  81,  81,  81,  81,  81,  81,  86,  87,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0,
				-3,  -3,  86,  87,  -3,  -3,  -3,  -3,  81,  81,  86,  87,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0,
				-3,  81,  86,  87,  92,  93,  81,  81,  81,  81,  86,  87,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0,
				-3,  81,  86,  87,  94,  95,  81,  81, 110,  -3,  86,  87,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0,
				-3,  81,  86,  87,  96,  97,  81, 110,  90,  91,  86,  87,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0,
				-3,  -3,  -3,  -3,  98,  99, 110,  81,  88,  89,  -3,  -3,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0,
				-3,  81,  86,  87,  81, 110,  81,  81, 106, 107,  86,  87,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0,
				-3,  81,  86,  87, 110,  81,  -3,  -3, 100, 101,  86,  87,   0,   0,   0,   0,   0,   0, 0, 0, 0, 0, 0, 0, 0,
			};
		map2 = new int[size] {

			    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			};
		player->SetStage(9);

		}
			
	else
	{
		//Error level doesn't exist or incorrect level number
		LOG("Failed to load level, stage %d doesn't exist", stage);
		return AppStatus::ERROR;
	}
	

	//Entities and objects
	i = 0;
	for (y = 0; y < LEVEL_HEIGHT; ++y)
	{
		for (x = 0; x < LEVEL_WIDTH; ++x)
		{
			tile = (Tile)map[i];
			if (tile == Tile::EMPTY)
			{
				map[i] = 0;
			}
			
			tile2 = (Tile)map2[i];
			if (tile2 == Tile::EMPTY)
			{
				map2[i] = 0;
			}
			else if (tile2 == Tile::PLAYER)
			{
				pos.x = x * TILE_SIZE;
				pos.y = y * TILE_SIZE + TILE_SIZE - 1;
				player->SetPos(pos);
				map2[i] = 0;
			}
			
			else if (tile2 == Tile::ITEM_HEART)
			{
				pos.x = x * TILE_SIZE;
				pos.y = y * TILE_SIZE + TILE_SIZE - 1;
				obj = new Object(pos, ObjectType::HEART);
				objects.push_back(obj);
				map2[i] = 0;
			}
			else if (tile2 == Tile::ITEM_RING)
			{
				pos.x = x * TILE_SIZE;
				pos.y = y * TILE_SIZE + TILE_SIZE - 1;
				obj = new Object(pos, ObjectType::THE_RING);
				objects.push_back(obj);
				map2[i] = 0;
			}
			++i;
		}
	}
	//Tile map
	level->Load(map, LEVEL_WIDTH, LEVEL_HEIGHT);
	
	delete[] map2;
	delete[] map;

	return AppStatus::OK;
}
void Scene::Update()
{
	Point p1, p2, posP;
	AABB box;
	Point p;

	//Switch between the different debug modes: off, on (sprites & hitboxes), on (hitboxes) 
	if (IsKeyPressed(KEY_F1))
	{
		debug = (DebugMode)(((int)debug + 1) % (int)DebugMode::SIZE);
	}
	//Debug levels instantly
	if (IsKeyPressed(KEY_F1))
	{
		debug = (DebugMode)(((int)debug + 1) % (int)DebugMode::SIZE);
	}
	else if (IsKeyPressed(KEY_ONE))
	{ 
		LoadLevel(1);
	
	}
	else if (IsKeyPressed(KEY_TWO)) 
	{ 
		LoadLevel(2);
		
	}
	else if (IsKeyPressed(KEY_THREE)) 
	{ 
		LoadLevel(3); 
		

	}
	else if (IsKeyPressed(KEY_FOUR))
	{ 
		LoadLevel(4); 
		
	}
	else if (IsKeyPressed(KEY_FIVE))
	{
		LoadLevel(5); 
		
	}
	else if (IsKeyPressed(KEY_SIX)) 
	{ 
		LoadLevel(6); 
		
	}
	else if (IsKeyPressed(KEY_SEVEN))
	{
		LoadLevel(7);

	}
	else if (IsKeyPressed(KEY_EIGHT))
	{
		LoadLevel(8);

	}
	else if (IsKeyPressed(KEY_NINE))
	{
		LoadLevel(9);

	}

	//Take out lives and die manually
	
	if ((player->GetStage() == 1 || player->GetStage() == 2 || player->GetStage() == 3)
		&& IsKeyPressed(KEY_M) && player->GetLives() >0 )
	{
		player->SetHp(0);
		player->Update();
		player->SetLifes(player->GetLives() - 1);
		player->SetHp(100);
		LoadLevel(1);

    }
	else if ((player->GetStage() == 4 || player->GetStage() == 5 || player->GetStage() == 6)
		&& IsKeyPressed(KEY_M) && player->GetLives() > 0)
	{
		player->SetHp(0);
		player->Update();
		player->SetLifes(player->GetLives() - 1);
		player->SetHp(100);
		LoadLevel(4);

	}

	//natural death
	if (player->GetHp() <= 0)
	{	
		

		if ((player->GetStage() == 1 || player->GetStage() == 2 || player->GetStage() == 3)
		 && player->GetLives() > 0)
	    {
			 
		   player->Update();
		   player->SetLifes(player->GetLives() - 1);
		   player->SetHp(100);
		   
		   
			   LoadLevel(1);
			  
		  
		    

	    }
		else if ((player->GetStage() == 4 || player->GetStage() == 5 || player->GetStage() == 6)
			&& player->GetLives() > 0)
		{
			player->Update();
			player->SetLifes(player->GetLives() - 1);
			player->SetHp(100);

			LoadLevel(4);

		}

	}
	
	
	

	//level transition
	//go

	
	if (player->GetStage() == 1 && player->GetHitbox().pos.x + (PLAYER_FRAME_SIZE_X-64) > WINDOW_WIDTH)
	{
		LoadLevel(2);
		
		
	}
	else if (player->GetStage() == 2 && player->GetHitbox().pos.x + (PLAYER_FRAME_SIZE_X - 64) > WINDOW_WIDTH)
	{
		
		LoadLevel(3);
	}
	else if (player->GetStage() == 3 && player->GetHitbox().pos.x + (PLAYER_FRAME_SIZE_X - 64) > WINDOW_WIDTH)
	{
		LoadLevel(4);
		
		
		
	}
	else if (player->GetStage() == 4 && player->GetHitbox().pos.x + (PLAYER_FRAME_SIZE_X - 64) > WINDOW_WIDTH)
	{
		LoadLevel(5);
		
	}
	else if (player->GetStage() == 5 && player->GetHitbox().pos.x + (PLAYER_FRAME_SIZE_X - 64) > WINDOW_WIDTH)
	{
		LoadLevel(6);
		
	}
	
	else if (player->GetStage() == 6 && player->GetHitbox().pos.x + (PLAYER_FRAME_SIZE_X - 64) > WINDOW_WIDTH)
	{
		LoadLevel(4);
		
	}
	//back
	else if (player->GetStage() == 2 && player->GetHitbox().pos.x < 0)
	{
		LoadLevel(1);
		posP.x =WINDOW_WIDTH - (PLAYER_FRAME_SIZE_X - 64);
		posP.y = WINDOW_HEIGHT - TILE_SIZE * 4;
		player->SetPos(posP);
	}
	else if (player->GetStage() == 3 && player->GetHitbox().pos.x < 0)
	{
		LoadLevel(2);
		posP.x = WINDOW_WIDTH - (PLAYER_FRAME_SIZE_X - 64);
		posP.y = WINDOW_HEIGHT - TILE_SIZE * 4;
		player->SetPos(posP);
	}
	else if (player->GetStage() == 4 && player->GetHitbox().pos.x < 0)
	{
		LoadLevel(6);
		posP.x = WINDOW_WIDTH - (PLAYER_FRAME_SIZE_X - 64);
		posP.y = WINDOW_HEIGHT - TILE_SIZE * 3;
		player->SetPos(posP);
	}
	else if (player->GetStage() == 5 && player->GetHitbox().pos.x < 0)
	{
		LoadLevel(4);
		posP.x = WINDOW_WIDTH - (PLAYER_FRAME_SIZE_X - 64);
		posP.y = WINDOW_HEIGHT - TILE_SIZE * 3;
		player->SetPos(posP);
	}
	else if (player->GetStage() == 6 && player->GetHitbox().pos.x < 0)
	{
		LoadLevel(5);
		posP.x = WINDOW_WIDTH - (PLAYER_FRAME_SIZE_X - 64);
		posP.y = WINDOW_HEIGHT - TILE_SIZE * 3;
		player->SetPos(posP);
	}

	level->Update();
	player->Update();
	

	if (player->GetStage() == 1 || player->GetStage() == 2 || player->GetStage() == 3)
	{
		/*UpdateMusicStream(musics[0]);*/
		
	}
	else if (player->GetStage() == 4 || player->GetStage() == 5 || player->GetStage() == 6)
	{
		UpdateMusicStream(musics[1]);
	}
	
	
	CheckCollisions();
}
void Scene::Render()
{
	BeginMode2D(camera);

	level->Render();
	
	
	if (debug == DebugMode::OFF || debug == DebugMode::SPRITES_AND_HITBOXES)
	{
		RenderObjects();
		player->Draw();
		
	}
	if (debug == DebugMode::SPRITES_AND_HITBOXES || debug == DebugMode::ONLY_HITBOXES)
	{
		RenderObjectsDebug(YELLOW);
		player->DrawDebug(GREEN);
		
	}

	EndMode2D();

	RenderGUI();
}
void Scene::Release()
{
	level->Release();
	
	player->Release();
	
	
	ClearLevel();
}
void Scene::CheckCollisions()
{
	AABB player_box, obj_box, soldier_box;

	player_box = player->GetHitbox();
	
	auto it = objects.begin();
	
	

	
	while (it != objects.end())
	{
		
		obj_box = (*it)->GetHitbox();
		if (player_box.TestAABB(obj_box) && (*it)->GetType() == ObjectType::HEART)
		{
			sound = LoadSound("Images/Heart.wav");
			PlaySound(sound);
			player->IncrLifes((*it)->Points());

			//Delete the object
			delete* it;
			//Erase the object from the vector and get the iterator to the next valid element
			it = objects.erase(it);
		}
		else if (player_box.TestAABB(obj_box) && (*it)->GetType() == ObjectType::THE_RING)
		{
			sound = LoadSound("Images/Item.wav");
			PlaySound(sound);
			player->SetWin(true);
			
			delete* it;
			//Erase the object from the vector and get the iterator to the next valid element
			it = objects.erase(it);
		}
		else
		{
			//Move to the next object
			++it;
		}
	}
	
}
void Scene::ClearLevel()
{
	Point p;
	p.x = WINDOW_WIDTH + 400;
	p.y = 0;
	for (Object* obj : objects)
	{
		delete obj;
	}
	objects.clear();
	for (Object* obj : objects2)
	{
		delete obj;
	}
	objects2.clear();
	
	
	
}
void Scene::RenderObjects() const
{
	for (Object* obj : objects)
	{
		obj->Draw();
	}
	for (Object* obj : objects2)
	{
		obj->Draw();
	}
}
void Scene::RenderObjectsDebug(const Color& col) const
{
	for (Object* obj : objects)
	{
		obj->DrawDebug(col);
	}
}
void Scene::RenderGUI() const
{
	//Temporal approach
	DrawText(TextFormat("SCORE : %d", player->GetScore()), 10, 1, 5, LIGHTGRAY);
	DrawText(TextFormat("LIFES : %d", player->GetLives()), 10,11, 5, LIGHTGRAY);
	DrawText(TextFormat("HP BAR : %d", player->GetHp()), 10, 21, 5, LIGHTGRAY);

}

