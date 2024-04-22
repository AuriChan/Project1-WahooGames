#include "Enemy.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include <raymath.h>

Enemy::Enemy(const Point& p, eState s, eLook view) :
	Entity(p, ENEMY_PHYSICAL_WIDTH, ENEMY_PHYSICAL_HEIGHT, ENEMY_FRAME_SIZE_X, ENEMY_FRAME_SIZE_Y)
{
	state = s;
	look = view;
	map = nullptr;
	
}
Enemy::~Enemy()
{
}
AppStatus Enemy::Initialise()
{
	int i;
	const int n = ENEMY_FRAME_SIZE_Y;
	const int m = ENEMY_FRAME_SIZE_X;

	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(ResourceImages::IMG_ENEMY, "Images/enemy.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}

	render = new Sprite(data.GetTexture(ResourceImages::IMG_ENEMY));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for player sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations((int)EnemyAnim::NUM_ANIMATIONS);

	sprite->SetAnimationDelay((int)EnemyAnim::IDLE_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)EnemyAnim::IDLE_RIGHT, { 1 * m, 3 * n, m, n });
	sprite->SetAnimationDelay((int)EnemyAnim::IDLE_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)EnemyAnim::IDLE_LEFT, { 1 * m, 3* n, -m, n });

	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_RIGHT, ANIM_DELAY);
	for (i = 0; i < 3; ++i)
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, {  (float) i * m ,  3 *n, m, n });
	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_LEFT, ANIM_DELAY);
	for (i = 0; i < 3; ++i)
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { (float) i * m, 3*n, -m, n });


	sprite->SetAnimation((int)EnemyAnim::IDLE_RIGHT);

	return AppStatus::OK;
}

void Enemy::SetStage(int n)
{
	stageC = n;
}
int Enemy::GetStage()const
{
	return stageC;
}
void Enemy::SetLifes(int l)
{
	lifes = l;
}

int Enemy::GetLives()const
{
	return lifes;
}
eState Enemy::GetState()const
{
	return state;
};
void Enemy:: SetState(eState s)
{
	state = s;
};

void Enemy::SetTileMap(TileMap* tilemap)
{
	map = tilemap;
}
bool Enemy::IsLookingRight() const
{
	return look == eLook::RIGHT;
}
bool Enemy::IsLookingLeft() const
{
	return look == eLook::LEFT;
}

void Enemy::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
EnemyAnim Enemy::GetAnimation()
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	return (EnemyAnim)sprite->GetAnimation();
}
void Enemy::Stop()
{
	dir = { 0,0 };
	state = eState::IDLE;
	if (IsLookingRight())	SetAnimation((int)EnemyAnim::IDLE_RIGHT);
	else					SetAnimation((int)EnemyAnim::IDLE_LEFT);
}
void Enemy::StartWalkingLeft()
{
	state = eState::WALKING;
	look = eLook::LEFT;
	SetAnimation((int)EnemyAnim::WALKING_LEFT);
}
void Enemy::StartWalkingRight()
{
	state = eState::WALKING;
	look = eLook::RIGHT;
	SetAnimation((int)EnemyAnim::WALKING_RIGHT);
}



void Enemy::ChangeAnimRight()
{
	look = eLook::RIGHT;
	switch (state)
	{
	case eState::IDLE:	 SetAnimation((int)EnemyAnim::IDLE_RIGHT);    break;
	case eState::WALKING: SetAnimation((int)EnemyAnim::WALKING_RIGHT); break;
	
	}
}
void Enemy::ChangeAnimLeft()
{
	look = eLook::LEFT;
	switch (state)
	{
	case eState::IDLE:	 SetAnimation((int)EnemyAnim::IDLE_LEFT);    break;
	case eState::WALKING: SetAnimation((int)EnemyAnim::WALKING_LEFT); break;
	
	}
}
void Enemy::Update(int marginLeft, int marginRight)
{
	MoveX(marginLeft, marginRight);
	
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();
}
void Enemy::MoveX(int ml, int mr)
{
	AABB box;
	int prev_x = pos.x;
	
	if (state == eState::IDLE) StartWalkingRight();
	if (pos.x > ml && pos.x < (mr) && lookLeft == true)
	{
		pos.x -= ENEMY_SPEED ;

	}
	else if(pos.x > ml && pos.x < (mr) && lookRight == true)
	{
		pos.x += ENEMY_SPEED;
	}
	
	if (pos.x <= ml)
	{
		pos.x = ml + 1;
		lookLeft = false;
		lookRight = true;
		StartWalkingLeft();
		ChangeAnimLeft();
		
	}
    else if (pos.x >= (mr))
	{
		pos.x = (mr) - 1;
		lookLeft = true;
		StartWalkingRight();
		ChangeAnimRight();

		
		lookRight = false;
	}
	
}

void Enemy::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);

	DrawText(TextFormat("Position: (%d,%d)\nSize: %dx%d\nFrame: %dx%d", pos.x, pos.y, width, height, frame_width, frame_height), 18 * 16, 0, 8, LIGHTGRAY);
	DrawPixel(pos.x, pos.y, WHITE);
}
void Enemy::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(ResourceImages::IMG_PLAYER);
	data.ReleaseTexture(ResourceImages::IMG_ENEMY);

	render->Release();
}