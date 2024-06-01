
#include "Player.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include <raymath.h>

Player::Player(const Point& p, State s, Look view) :
	Entity(p, PLAYER_PHYSICAL_WIDTH, PLAYER_PHYSICAL_HEIGHT, PLAYER_FRAME_SIZE_X, PLAYER_FRAME_SIZE_Y)
{
	state = s;
	look = view;
	jump_delay = PLAYER_JUMP_DELAY;
	map = nullptr;
	score = 0;
	isClimbingUp = false;
	isClimbingDown = false;
	startedClimbing = false;
}
Player::~Player()
{
}
AppStatus Player::Initialise()
{
	int i;
	const int n = PLAYER_FRAME_SIZE_Y;
	const int m = PLAYER_FRAME_SIZE_X;

	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(ResourceImages::IMG_PLAYER, "Images/SimonBelmont.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}

	render = new Sprite(data.GetTexture(ResourceImages::IMG_PLAYER));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for player sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations((int)PlayerAnim::NUM_ANIMATIONS);

	sprite->SetAnimationDelay((int)PlayerAnim::IDLE_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::IDLE_RIGHT, { 0, 0, m, n });
	sprite->SetAnimationDelay((int)PlayerAnim::IDLE_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::IDLE_LEFT, { 0, 0, -m, n });

	sprite->SetAnimationDelay((int)PlayerAnim::WALKING_RIGHT, ANIM_DELAY);
	for (i = 0; i < 3; ++i)
		sprite->AddKeyFrame((int)PlayerAnim::WALKING_RIGHT, { (float)i * m, 0, m, n });
	sprite->SetAnimationDelay((int)PlayerAnim::WALKING_LEFT, ANIM_DELAY);
	for (i = 0; i < 3; ++i)
		sprite->AddKeyFrame((int)PlayerAnim::WALKING_LEFT, { (float)i * m, 0, -m, n });

	sprite->SetAnimationDelay((int)PlayerAnim::CROUCHING_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::CROUCHING_RIGHT, { 3 * m, 0, m, n });
	sprite->SetAnimationDelay((int)PlayerAnim::CROUCHING_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::CROUCHING_LEFT, { 3 * m, 0, -m, n });

	sprite->SetAnimationDelay((int)PlayerAnim::JUMPING_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::JUMPING_RIGHT, { 3 * m, 0, m, n });
	sprite->SetAnimationDelay((int)PlayerAnim::JUMPING_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::JUMPING_LEFT, { 3 * m, 0, -m, n });

	sprite->SetAnimationDelay((int)PlayerAnim::WHIP_IDLE_RIGHT, ANIM_DELAY);
	for (i = 0; i < 3; ++i)
		sprite->AddKeyFrame((int)PlayerAnim::WHIP_IDLE_RIGHT, { (float)i * m, 3 * n, m, n });
	sprite->SetAnimationDelay((int)PlayerAnim::WHIP_IDLE_LEFT, ANIM_DELAY);
	for (i = 0; i < 3; ++i)
		sprite->AddKeyFrame((int)PlayerAnim::WHIP_IDLE_LEFT, { (float)i * m, 3 * n, -m, n });

	sprite->SetAnimationDelay((int)PlayerAnim::WHIP_CROUCHING_RIGHT, ANIM_DELAY);
	for (i = 0; i < 3; ++i)
		sprite->AddKeyFrame((int)PlayerAnim::WHIP_CROUCHING_RIGHT, { (float)i * m, 4 * n, m, n });
	sprite->SetAnimationDelay((int)PlayerAnim::WHIP_CROUCHING_LEFT, ANIM_DELAY);
	for (i = 0; i < 3; ++i)
		sprite->AddKeyFrame((int)PlayerAnim::WHIP_CROUCHING_LEFT, { (float)i * m, 4 * n, -m, n });


	sprite->SetAnimationDelay((int)PlayerAnim::DEATH_RIGHT, ANIM_DELAY * 3);
	sprite->AddKeyFrame((int)PlayerAnim::DEATH_RIGHT, { (float)m,  n, m, n });
	sprite->AddKeyFrame((int)PlayerAnim::DEATH_RIGHT, { (float)2 * m,  n, m, n });


	sprite->SetAnimationDelay((int)PlayerAnim::DEATH_LEFT, ANIM_DELAY * 3);
	sprite->AddKeyFrame((int)PlayerAnim::DEATH_LEFT, { (float)m,  n, -m, n });
	sprite->AddKeyFrame((int)PlayerAnim::DEATH_LEFT, { (float)2 * m,  n, -m, n });

	sprite->SetAnimationDelay((int)PlayerAnim::CLIMBING_TOP_RIGHT, ANIM_DELAY * 2);
	sprite->AddKeyFrame((int)PlayerAnim::CLIMBING_TOP_RIGHT, { (float)4 * m,  0, m, n });
	sprite->AddKeyFrame((int)PlayerAnim::CLIMBING_TOP_RIGHT, { (float)1 * m,  0, m, n });

	sprite->SetAnimationDelay((int)PlayerAnim::CLIMBING_BOTTOM_LEFT, ANIM_DELAY * 2);
	sprite->AddKeyFrame((int)PlayerAnim::CLIMBING_BOTTOM_LEFT, { (float)5 * m,  0, -m, n });
	sprite->AddKeyFrame((int)PlayerAnim::CLIMBING_BOTTOM_LEFT, { (float)1 * m,  0, -m, n });

	sprite->SetAnimationDelay((int)PlayerAnim::WHIP_CLIMBING_TOP_RIGHT, ANIM_DELAY * 5);
	for (i = 0; i < 3; ++i)
	sprite->AddKeyFrame((int)PlayerAnim::WHIP_CLIMBING_TOP_RIGHT, { (float)i * m, 5 * n, m, n });

	sprite->SetAnimationDelay((int)PlayerAnim::WHIP_CLIMBING_BOTTOM_LEFT, ANIM_DELAY * 5);
	for (i = 0; i < 3; ++i)
	sprite->AddKeyFrame((int)PlayerAnim::WHIP_CLIMBING_BOTTOM_LEFT, { (float)i * m, 6 * n, -m, n });

	sprite->SetAnimation((int)PlayerAnim::IDLE_RIGHT);

	return AppStatus::OK;
}
void Player::InitScore()
{
	score = 0;
}
void Player::SetStage(int n)
{
	stageC = n;
}
int Player::GetStage()const
{
	return stageC;
}
void Player::SetLifes(int l)
{
	lifes = l;
}

int Player::GetLives()const
{
	return lifes;
}
void Player::SetFCount(int l)
{
	finalCountdown = l;
}
int Player::GetFCount()const
{
	return finalCountdown;
}
void Player::DecreaseFCount()
{
	finalCountdown--;
}
bool Player::GetOrb()const
{
	return spawnOrb;
}
void Player:: SetOrb(bool w)
{
	spawnOrb = w;
}
void Player::IncrScore(int n)
{
	score += n;
}
void Player::IncrLifes(int n)
{
	lifes += n;
}
int Player::GetScore()const
{
	return score;
}
bool Player::GetWin()const
{
	return win;
};
void Player::SetWin(bool w)
{
	win = w;
};
bool Player::GetKey()const
{
	return key;
}
void Player::SetKey(bool k)
{
	key = k;
}
bool Player:: GetTreasureKey()const
{
	return treasureKey;
}
void Player::SetTreasureKey(int k)
{
	treasureKey = k;
}
void Player::SetHp(int h)
{
	HpBar = h;
}
;
int Player::GetHp()const
{
	return HpBar;
};

int Player::GetPosY()const
{
	return pos.y;
}
int Player::GetPosx()const
{
	return pos.x;
}

void Player::SetLevel(int n)
{
	Level = n;
}
int Player:: GetLevel()const
{
	return Level;
}


void Player::SetTileMap(TileMap* tilemap)
{
	map = tilemap;
}
bool Player::IsLookingRight() const
{
	return look == Look::RIGHT;
}
bool Player::IsLookingLeft() const
{
	return look == Look::LEFT;
}
bool Player::IsAscending() const
{
	return dir.y < -PLAYER_LEVITATING_SPEED;
}
bool Player::IsLevitating() const
{
	return abs(dir.y) <= PLAYER_LEVITATING_SPEED;
}
bool Player::IsDescending() const
{
	return dir.y > PLAYER_LEVITATING_SPEED;
}
void Player::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
PlayerAnim Player::GetAnimation()
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	return (PlayerAnim)sprite->GetAnimation();
}
void Player::Stop()
{
	dir = { 0,0 };
	state = State::IDLE;
	if (IsLookingRight())	SetAnimation((int)PlayerAnim::IDLE_RIGHT);
	else					SetAnimation((int)PlayerAnim::IDLE_LEFT);
}
void Player::StartWalkingLeft()
{
	state = State::WALKING;
	look = Look::LEFT;
	SetAnimation((int)PlayerAnim::WALKING_LEFT);
}
void Player::StartWalkingRight()
{
	state = State::WALKING;
	look = Look::RIGHT;
	SetAnimation((int)PlayerAnim::WALKING_RIGHT);
}
void Player::StartFalling()
{
	dir.y = PLAYER_SPEED * 2;
	state = State::FALLING;
	if (IsLookingRight())	SetAnimation((int)PlayerAnim::CROUCHING_RIGHT);
	else					SetAnimation((int)PlayerAnim::CROUCHING_LEFT);
}
void Player::StartJumping()
{
	dir.y = -PLAYER_JUMP_FORCE;
	state = State::JUMPING;
	if (IsLookingRight())	SetAnimation((int)PlayerAnim::JUMPING_RIGHT);
	else					SetAnimation((int)PlayerAnim::JUMPING_LEFT);
	jump_delay = PLAYER_JUMP_DELAY;
}
void Player::StartCrouching()
{
	state = State::CROUCHING;
	if (IsLookingRight())	SetAnimation((int)PlayerAnim::CROUCHING_RIGHT);
	else					SetAnimation((int)PlayerAnim::CROUCHING_LEFT);
}
void Player::StartAttacking()
{

	if (state == State::CROUCHING)
	{
		isCrouching = true;
		state = State::ATTACKING;
		if (IsLookingRight())
		{
			SetAnimation((int)PlayerAnim::WHIP_CROUCHING_RIGHT);
			Sprite* sprite = dynamic_cast<Sprite*>(render);
			sprite->SetSingleMode();
			
		}
		else
		{
			SetAnimation((int)PlayerAnim::WHIP_CROUCHING_LEFT);
			Sprite* sprite = dynamic_cast<Sprite*>(render);
			sprite->SetSingleMode();

		}
	}
	else if(state == State::IDLE)
	{
		state = State::ATTACKING;
		if (IsLookingRight())
		{
			SetAnimation((int)PlayerAnim::WHIP_IDLE_RIGHT);
			Sprite* sprite = dynamic_cast<Sprite*>(render);
			sprite->SetSingleMode();

		}
		else
		{
			SetAnimation((int)PlayerAnim::WHIP_IDLE_LEFT);
			Sprite* sprite = dynamic_cast<Sprite*>(render);
			sprite->SetSingleMode();

		}
	}
	else if (state == State::WALKING)
	{
		state = State::ATTACKING;
		if (IsLookingRight())
		{
			SetAnimation((int)PlayerAnim::WHIP_IDLE_RIGHT);
			Sprite* sprite = dynamic_cast<Sprite*>(render);
			sprite->SetSingleMode();

		}
		else
		{
			SetAnimation((int)PlayerAnim::WHIP_IDLE_LEFT);
			Sprite* sprite = dynamic_cast<Sprite*>(render);
			sprite->SetSingleMode();

		}
	}
	else if (state == State::JUMPING)
	{
		state = State::ATTACKING;
		if (IsLookingRight())
		{
			SetAnimation((int)PlayerAnim::WHIP_IDLE_RIGHT);
			Sprite* sprite = dynamic_cast<Sprite*>(render);
			sprite->SetSingleMode();

		}
		else
		{
			SetAnimation((int)PlayerAnim::WHIP_IDLE_LEFT);
			Sprite* sprite = dynamic_cast<Sprite*>(render);
			sprite->SetSingleMode();

		}
	}
	else if (state == State::CLIMBING)
	{
		return;
	}
	
	
	data.LoadSound(ResourceAudio::SOUND_ATTACK, "Images/WhipMissTarget.wav");
	data.StartSound(ResourceAudio::SOUND_ATTACK);
}
void Player::StartClimbingUp()
{
	state = State::CLIMBING;
	SetAnimation((int)PlayerAnim::CLIMBING_TOP_RIGHT);
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetManualMode();
}
void Player::StartClimbingDown()
{
	state = State::CLIMBING;
	SetAnimation((int)PlayerAnim::CLIMBING_BOTTOM_LEFT);
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetManualMode();

}
void Player::Death()
{


	state = State::DEAD;
	if (IsLookingRight())
	{
		SetAnimation((int)PlayerAnim::DEATH_RIGHT);
		Sprite* sprite = dynamic_cast<Sprite*>(render);
		sprite->SetSingleMode();

	}
	else
	{
		SetAnimation((int)PlayerAnim::DEATH_LEFT);
		Sprite* sprite = dynamic_cast<Sprite*>(render);
		sprite->SetSingleMode();

	}

}

void Player::ChangeAnimRight()
{
	look = Look::RIGHT;
	switch (state)
	{
	case State::IDLE:	 SetAnimation((int)PlayerAnim::IDLE_RIGHT);    break;
	case State::WALKING: SetAnimation((int)PlayerAnim::WALKING_RIGHT); break;
	case State::JUMPING: SetAnimation((int)PlayerAnim::JUMPING_RIGHT); break;
	case State::FALLING: SetAnimation((int)PlayerAnim::CROUCHING_RIGHT); break;
	case State::CROUCHING: SetAnimation((int)PlayerAnim::CROUCHING_RIGHT); break;
	}
}
void Player::ChangeAnimLeft()
{
	look = Look::LEFT;
	switch (state)
	{
	case State::IDLE:	 SetAnimation((int)PlayerAnim::IDLE_LEFT);    break;
	case State::WALKING: SetAnimation((int)PlayerAnim::WALKING_LEFT); break;
	case State::JUMPING: SetAnimation((int)PlayerAnim::JUMPING_LEFT); break;
	case State::FALLING: SetAnimation((int)PlayerAnim::CROUCHING_LEFT); break;
	case State::CROUCHING: SetAnimation((int)PlayerAnim::CROUCHING_LEFT); break;
	}
}
void Player::Update()
{
	timer++;
	timer %= 11;
	//Player doesn't use the "Entity::Update() { pos += dir; }" default behaviour.
	//Instead, uses an independent behaviour for each axis.

	if (HpBar == 0)
	{
		Death();
	}
	else if (IsKeyPressed(KEY_SPACE) && state != State::ATTACKING && state != State::DEAD)
	{
		StartAttacking();
	}
	else
	{

		MoveX();
		MoveY();

	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();


	if (sprite->GetIsFinished())
	{
		sprite->SetIsFinished(false);
		if (isCrouching)
		{
			StartCrouching();
		}
		else
		{
			state = State::IDLE;
			Stop();
		}

		isCrouching = false;
	}

}
void Player::MoveX()
{
	AABB box;
	int prev_x = pos.x;

	//We can only go up and down while climbing
	if (state == State::CLIMBING)	return;
	if (state == State::DEAD) return;

	if (IsKeyDown(KEY_DOWN) && state != State::ATTACKING)
	{
		if (state == State::JUMPING) return;
		else if (state == State::IDLE) StartCrouching();
		else if (state == State::WALKING) StartCrouching();

	}
	

	else if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && state != State::ATTACKING)
	{
		if (pos.x < 0) { pos.x = 0; }

		else { pos.x -= PLAYER_SPEED; }

		if (state == State::IDLE) StartWalkingLeft();
		else if (state == State::CROUCHING) StartWalkingLeft();
		
		else
		{
			if (IsLookingRight()) ChangeAnimLeft();
		}

		box = GetHitbox();
		if (map->TestCollisionWallLeft(box))
		{
			pos.x = prev_x;
			if (state == State::WALKING) Stop();
		}
	}

	else if (IsKeyDown(KEY_RIGHT) && state != State::ATTACKING)
	{
		if (pos.x >= WINDOW_WIDTH - (PLAYER_FRAME_SIZE_X - 64))
		{
			pos.x = WINDOW_WIDTH - (PLAYER_FRAME_SIZE_X - 64);
		}

		pos.x += PLAYER_SPEED;
		if (state == State::IDLE) StartWalkingRight();
		else if (state == State::CROUCHING) StartWalkingRight();
		else
		{
			if (IsLookingLeft()) ChangeAnimRight();
		}

		box = GetHitbox();
		if (map->TestCollisionWallRight(box))
		{
			pos.x = prev_x;
			if (state == State::WALKING) Stop();
		}
	}

	else
	{
		if (state == State::WALKING || state == State::CROUCHING) Stop();
	}
}
void Player::MoveY()
{
	AABB box;

	if (state == State::JUMPING)
	{
		LogicJumping();
	}
	else if (state == State::CLIMBING)
	{
		LogicClimbing();
	}
	else //idle, walking, falling
	{
		pos.y += PLAYER_SPEED * 2;
		box = GetHitbox();
		if (map->TestCollisionGround(box, &pos.y))
		{
			if (state == State::FALLING) Stop();

			if (IsKeyPressed(KEY_UP) && state != State::DEAD)
			{
				box = GetHitbox();
				if (map->TestOnLadder(box, &pos.x))
					StartClimbingUp();
				else
					StartJumping();
			}
			else if (IsKeyDown(KEY_DOWN) && state != State::DEAD)
			{
				//To climb up the ladder, we need to check the control point (x, y)
				//To climb down the ladder, we need to check pixel below (x, y+1) instead
				box = GetHitbox();
				box.pos.y++;
				if (map->TestOnLadderTop(box, &pos.x) && !startedClimbing) //This has to be TestOnLadderTop()
				{
					
					StartClimbingDown();
					pos.y += 16;
					pos.x -= 16;
				}

			}
			

		}
		else
		{
			if (state != State::FALLING) StartFalling();
		}
	}
}
void Player::LogicJumping()
{
	AABB box, prev_box;
	int prev_y;

	jump_delay--;
	if (jump_delay == 0)
	{
		prev_y = pos.y;
		prev_box = GetHitbox();

		pos.y += dir.y;
		dir.y += GRAVITY_FORCE;
		jump_delay = PLAYER_JUMP_DELAY;

		//Is the jump finished?
		if (dir.y > PLAYER_JUMP_FORCE)
		{
			dir.y = PLAYER_SPEED * 2;
			StartFalling();
		}
		else
		{
			//Jumping is represented with 3 different states
			if (IsAscending())
			{
				if (IsLookingRight())	SetAnimation((int)PlayerAnim::JUMPING_RIGHT);
				else					SetAnimation((int)PlayerAnim::JUMPING_LEFT);
			}
			else if (IsDescending())
			{
				if (IsLookingRight())	SetAnimation((int)PlayerAnim::CROUCHING_RIGHT);
				else					SetAnimation((int)PlayerAnim::CROUCHING_LEFT);
			}
		}
		//We check ground collision when jumping down
		if (dir.y >= 0)
		{
			box = GetHitbox();

			//A ground collision occurs if we were not in a collision state previously.
			//This prevents scenarios where, after levitating due to a previous jump, we found
			//ourselves inside a tile, and the entity would otherwise be placed above the tile,
			//crossing it.
			if (!map->TestCollisionGround(prev_box, &prev_y) &&
				map->TestCollisionGround(box, &pos.y))
			{
				Stop();
			}
		}
	}
}
void Player::LogicClimbing()
{
	AABB box;
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	int tmp;


	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_RIGHT))
	{
		isClimbingUp = true;
		isClimbingDown = false;
		pos.y -= PLAYER_LADDER_SPEED;
		pos.x += PLAYER_LADDER_SPEED;
		sprite->NextFrame();
	}
	else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_LEFT))
	{
		isClimbingUp = false;
		isClimbingDown = true;
		pos.y += PLAYER_LADDER_SPEED;
		pos.x -= PLAYER_LADDER_SPEED;
		sprite->NextFrame(); // Change the sprite to go downwards, check what sprite is
	}

	//It is important to first check LadderTop due to its condition as a collision ground.
	//By doing so, we ensure that we don't stop climbing down immediately after starting the descent.
	box = GetHitbox();

	if (map->TestCollisionGround(box, &pos.y))
	{
		//Case leaving the ladder descending.
		Stop();
		sprite->SetAutomaticMode();
	}
	else if (!map->TestOnLadder(box, &tmp))
	{
		//Case leaving the ladder ascending.
		//If we are not in a LadderTop, colliding ground or in the Ladder it means we are leaving
		//ther ladder ascending.
		Stop();
		sprite->SetAutomaticMode();
	}
	else
	{
		//if (GetAnimation() != PlayerAnim::CLIMBING_BOTTOM_LEFT)	SetAnimation((int)PlayerAnim::CLIMBING_BOTTOM_LEFT); //the problem
		if (isClimbingUp && GetAnimation() != PlayerAnim::CLIMBING_TOP_RIGHT)	SetAnimation((int)PlayerAnim::CLIMBING_TOP_RIGHT);
		else if (!isClimbingUp && GetAnimation() != PlayerAnim::CLIMBING_BOTTOM_LEFT) SetAnimation((int)PlayerAnim::CLIMBING_BOTTOM_LEFT);
	}
}
AABB Player::GetWhipHitbox() 
{
	if (state == State::ATTACKING && IsLookingRight() && !isCrouching)
	{
		if (hit == false)
		{
			hit = true;
			hitTimer = timer;
		}
		else if (hit == true && hitTimer == timer)
		{
			hit = true;
			Point p(pos.x + 12, pos.y - 15);
			AABB hitbox(p, 27, 8);
			return hitbox;
		}
		Point p(pos.x + 12, pos.y - 15);
		AABB hitbox(p, 27, 8);
		return hitbox;
	}
	else if (state == State::ATTACKING && IsLookingLeft() && !isCrouching)
	{
		if (hit == false)
		{
			hit = true;
			hitTimer = timer;
		}
		else if (hit == true && hitTimer == timer)
		{
			hit = true;
			Point p(pos.x - 27, pos.y - 15);
			AABB hitbox(p, 27, 8);
			return hitbox;
		}
		Point p(pos.x - 27, pos.y - 15);
		AABB hitbox(p, 27, 8);
		return hitbox;
	}
	else if (state == State::ATTACKING && IsLookingRight() && isCrouching)
	{
		if (hit == false)
		{
			hit = true;
			hitTimer = timer;
		}
		else if (hit == true && hitTimer == timer)
		{
			hit = true;
			Point p(pos.x + 12, pos.y);
			AABB hitbox(p, 27, 8);
			return hitbox;
		}
		Point p(pos.x + 12, pos.y - 15);
		AABB hitbox(p, 27, 8);
		return hitbox;
	}
	else if (state == State::ATTACKING && IsLookingLeft() && isCrouching)
	{
		if (hit == false)
		{
			hit = true;
			hitTimer = timer;
		}
		else if (hit == true && hitTimer == timer)
		{
			hit = true;
			Point p(pos.x - 27, pos.y - 15);
			AABB hitbox(p, 27, 8);
			return hitbox;
		}
		Point p(pos.x - 27, pos.y - 15);
		AABB hitbox(p, 27, 8);
		return hitbox;
	}
}
void Player::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
	if (state == State::ATTACKING && IsLookingRight() && !isCrouching)
	{
		Entity::DrawHitbox(pos.x + 12, pos.y - 15, 27, 8, col);
	}
	else if (state == State::ATTACKING && IsLookingLeft() && !isCrouching)
	{
		Entity::DrawHitbox(pos.x - 27, pos.y - 15, 27, 8, col);
	}
	else if (state == State::ATTACKING && IsLookingRight() && isCrouching)
	{
		Entity::DrawHitbox(pos.x + 12, pos.y - 8, 27, 8, col);
	}
	else if (state == State::ATTACKING && IsLookingLeft() && isCrouching)
	{
		Entity::DrawHitbox(pos.x - 27, pos.y - 8, 27, 8, col);
	}
	

	DrawText(TextFormat("Position: (%d,%d)\nSize: %dx%d\nFrame: %dx%d", pos.x, pos.y, width, height, frame_width, frame_height), 18 * 16, 0, 8, LIGHTGRAY);
	DrawPixel(pos.x, pos.y, WHITE);
}
void Player::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(ResourceImages::IMG_PLAYER);

	CloseAudioDevice();

	render->Release();
}
