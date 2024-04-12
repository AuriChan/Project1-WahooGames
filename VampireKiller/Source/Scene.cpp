#include "Scene.h"
#include "Globals.h"
#include <stdio.h>

Scene::Scene()
{
	level = nullptr;
}
Scene::~Scene()
{
	if (level != nullptr)
	{
		level->Release();
		delete level;
		level = nullptr;
	}
}
AppStatus Scene::Init()
{
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

	return AppStatus::OK;
}
AppStatus Scene::LoadLevel(int stage)
{
	int size;

	if (stage == 1)
	{
		size = LEVEL_WIDTH * LEVEL_HEIGHT;
		int map[] = {
				 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	  0,   0,   0,  13,
				 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	  0,   0,   0,   9,
				0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  10,
				 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	  0,   0,   0,   9,
				0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	  0,   0,   0,  10,
				 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,	  0,   0,   0,   9,
				0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  17,  18,  17,  18,  22,  23,	  0,   0,   0,  10,
				 0,  0,  0,   0,   0,  0,   0,   0,  0,  0,  0,  17,  18,   0,   0,   0,   0,   0,   0,  20,  21,	  0,   0,   0,   9,
				0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  20,  21,	  0,   0,   0,  10,
				 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  20,  21,	  0,   0,   0,   9,
				0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  22,  23,   9,   0,  20,  21,	  0,   0,   0,  10,
				0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  20,  21,  10,   0,  20,  21,	  0,   0,   0,   9,
				0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  20,  21,   9,   0,  20,  21,	  0,   0,   0,  10,
				 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  20,  21,  10,   0,  20,  21,	  0,   0,   0,   9,
				0,  0,  18,  17,  18,  13,   0,   0,   0,   0,  13,  17,  18,  13,   0,  20,  21,   9,   0,  20,  21,	  0,   0,   0,  10,
				 0,   0,   2,   5,   6,  40,   0,   0,   0,   0,  41,   1,   2,   9,   0,  20,  21,  10,   0,  20,  21,	  0,   0,   0,   9,
				0,   0,   4,   7,   8,  13,  14,  15,  16,  11,  12,   3,   4,  10,  14,  15,  16,  13,  14,  15,  16,   0,  13,   0,  10
		};
		level->Load(map, LEVEL_WIDTH, LEVEL_HEIGHT);
	}
	else
	{
		//Error level doesn't exist or incorrect level number
		LOG("Failed to load level, stage %d doesn't exist", stage);
		return AppStatus::ERROR;
	}
	return AppStatus::OK;
}
void Scene::HandleInputPlayer()
{
}
void Scene::Update()
{
}
void Scene::Render()
{
	level->Render();
}
void Scene::Release()
{
	level->Release();
}