#include "EnemyManager.h"
#include "Soldier.h"
#include "SkullTurret.h"
#include "Medusa.h"

EnemyManager::EnemyManager()
{
	shots = nullptr;
	timer = 0;
	
}
EnemyManager::~EnemyManager()
{
	Release();
}
AppStatus EnemyManager::Initialise()
{
	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(ResourceImages::IMG_ENEMY, "images/enemy.png") != AppStatus::OK)
	{
		LOG("Failed to load enemies sprite texture");
		return AppStatus::ERROR;
	}

	return AppStatus::OK;
}
void EnemyManager::SetShotManager(ShotManager* shots)
{
	this->shots = shots;
}
void EnemyManager::Add(const Point& pos, EnemyType type, const AABB& area, Look look)
{
	Enemy* enemy;
	

	if (type == EnemyType::SLIME)
	{
		enemy = new Slime(pos, SLIME_PHYSICAL_WIDTH, SLIME_PHYSICAL_HEIGHT, SLIME_FRAME_SIZE_X, SLIME_FRAME_SIZE_Y);
	}
	else if (type == EnemyType::TURRET)
	{
		enemy = new Turret(pos, TURRET_PHYSICAL_WIDTH, TURRET_PHYSICAL_HEIGHT, TURRET_FRAME_SIZE_X, TURRET_FRAME_SIZE_Y);
		
	}
	else if (type == EnemyType::MEDUSA)
	{
		
		enemy = new Medusa(pos, MEDUSA_PHYSICAL_WIDTH, MEDUSA_PHYSICAL_HEIGHT, MEDUSA_FRAME_SIZE, MEDUSA_FRAME_SIZE);
		enemy->SetType(EnemyType::MEDUSA);
		
		
	}
	else
	{
		LOG("Internal error: trying to add a new enemy with invalid type");
		return;
	}

	enemy->Initialise(look, area);
	enemies.push_back(enemy);
}
AABB EnemyManager::GetEnemyHitBox(const Point& pos, EnemyType type) const
{
	int width, height;
	if (type == EnemyType::SLIME)
	{
		width = SLIME_PHYSICAL_WIDTH;
		height = SLIME_PHYSICAL_HEIGHT;
	}
	else if (type == EnemyType::TURRET)
	{
		width = TURRET_PHYSICAL_WIDTH;
		height = TURRET_PHYSICAL_HEIGHT;
	}
	else if (type == EnemyType::MEDUSA)
	{
		width = MEDUSA_PHYSICAL_WIDTH;
		height = MEDUSA_PHYSICAL_HEIGHT;
	}
	else
	{
		LOG("Internal error while computing hitbox for an invalid enemy type");
		return {};
	}
	Point p(pos.x, pos.y - (height - 1));
	AABB hitbox(p, width, height);
	return hitbox;
}
void EnemyManager::Update( AABB& player_hitbox)
{
	bool shoot;
	Point p, d;

	if (timer > 0)
	{
		timer--;
	}
	else
	{
		timer = 0;
	}
	
	
	for (Enemy* enemy : enemies)
	{
		shoot = enemy->Update(player_hitbox);
		if (shoot)
		{
			enemy->GetShootingPosDir(&p, &d);
			shots->Add(p, d);
		}
	}
}
void EnemyManager::CheckCollisionsEnemies(AABB player_box, Player *p)
{
	AABB enemy_box;
	auto it = enemies.begin();

	
	while (it != enemies.end())
	{

		enemy_box = (*it)->GetHitbox();

		if (player_box.TestAABB(enemy_box))
		{
			switch ((*it)->GetType())
			{
			case EnemyType::SLIME:
			{
				(*it)->ReceiveDamage();

				if ((*it)->GetLifes() <= 0)
				{
					delete* it;
 					it = enemies.erase(it);
					p->IncrScore(200);
				}
				else
				{
					++it;
				}

				break;
			}
			case EnemyType::TURRET:

				(*it)->ReceiveDamage();

				if ((*it)->GetLifes() <= 0)
				{
					delete* it;
					it = enemies.erase(it);
					p->IncrScore(300);
				}
				else
				{
					++it;
				}
				break;
			case EnemyType::MEDUSA:

				(*it)->ReceiveDamage();

				if ((*it)->GetLifes() <= 0)
				{
					p->IncrScore(2000);
					delete* it;
					it = enemies.erase(it);
					
					p->SetOrb(true);
					
				}
				else
				{
					++it;
				}
				break;
			default:
				break;
			}
		}
		else
		{
			++it;
		}
	}
	
	
}
void EnemyManager::CheckCollisionsPlayer(AABB player_box, Player* p)
{
	AABB enemy_box;
	auto it = enemies.begin();

	while (it != enemies.end())
	{
		enemy_box = (*it)->GetHitbox();
		if (player_box.TestAABB(enemy_box))
		{
			switch ((*it)->GetType())
			{
			case EnemyType::SLIME:
				if (timer == 0)
				{
					p->SetHp((p->GetHp()) - (*it)->GetDamage());
					timer = 120;
				}
				++it;
				break;
			case EnemyType::TURRET:
				if (timer == 0)
				{
					p->SetHp((p->GetHp()) - (*it)->GetDamage());
					timer = 120;
				}
				++it;
				break;
			case EnemyType::MEDUSA:
				if (timer == 0)
				{
					p->SetHp((p->GetHp()) - (*it)->GetDamage());
					timer = 120;
				}
				++it;
				break;
			default:
				break;
			}
		}
		else
		{
			++it;
		}
	}
}
void EnemyManager::Draw() const
{
	for (const Enemy* enemy : enemies)
		enemy->Draw();
}
void EnemyManager::DrawDebug() const
{
	for (const Enemy* enemy : enemies)
	{
		enemy->DrawVisibilityArea(DARKGRAY);
		enemy->DrawHitbox(RED);
	}
}
void EnemyManager::Release()
{
	for (Enemy* enemy : enemies)
		delete enemy;
	enemies.clear();
}