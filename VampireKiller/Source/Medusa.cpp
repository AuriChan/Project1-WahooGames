#include "Medusa.h"
#include "Sprite.h"

Medusa::Medusa(const Point& p, int width, int height, int frame_width, int frame_height) :
	Enemy(p, width, height, frame_width, frame_height)
{
	attack_delay = 0;
	state = MedusaState::ROAMING;

	current_step = 0;
	current_frames = 0;

	lifes = 272;
	damage = 4;
}
Medusa::~Medusa()
{
}
AppStatus Medusa::Initialise(Look look, const AABB& area)
{
	int i;
	const int n = MEDUSA_FRAME_SIZE;

	ResourceManager& data = ResourceManager::Instance();
	render = new Sprite(data.GetTexture(ResourceImages::IMG_ENEMY));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for slime sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations((int)MedusaAnim::NUM_ANIMATIONS);

	sprite->SetAnimationDelay((int)MedusaAnim::IDLE_RIGHT, MEDUSA_ANIM_DELAY);
	sprite->AddKeyFrame((int)MedusaAnim::IDLE_RIGHT, { 0, 1 * n, n, n });
	sprite->SetAnimationDelay((int)MedusaAnim::IDLE_LEFT, MEDUSA_ANIM_DELAY);
	sprite->AddKeyFrame((int)MedusaAnim::IDLE_LEFT, { 0, 1 * n, -n, n });

	sprite->SetAnimationDelay((int)MedusaAnim::WALKING_RIGHT, MEDUSA_ANIM_DELAY);
	for (i = 0; i < 2; ++i)
		sprite->AddKeyFrame((int)MedusaAnim::WALKING_RIGHT, { (float)i * n, 1 * n, n, n });
	sprite->SetAnimationDelay((int)MedusaAnim::WALKING_LEFT, MEDUSA_ANIM_DELAY);
	for (i = 0; i < 2; ++i)
		sprite->AddKeyFrame((int)MedusaAnim::WALKING_LEFT, { (float)i * n, 1 * n, -n, n });

	sprite->SetAnimationDelay((int)MedusaAnim::ATTACK_RIGHT, MEDUSA_ANIM_DELAY);
	sprite->AddKeyFrame((int)MedusaAnim::ATTACK_RIGHT, { 0, 1 * n, n, n });
	sprite->AddKeyFrame((int)MedusaAnim::ATTACK_RIGHT, { n, 1 * n, n, n });
	sprite->SetAnimationDelay((int)MedusaAnim::ATTACK_LEFT, MEDUSA_ANIM_DELAY);
	sprite->AddKeyFrame((int)MedusaAnim::ATTACK_LEFT, { 0, 1 * n, -n, n });
	sprite->AddKeyFrame((int)MedusaAnim::ATTACK_LEFT, { n, 1 * n, -n, n });

	this->look = look;
	if (look == Look::LEFT)        sprite->SetAnimation((int)MedusaAnim::IDLE_LEFT);
	else if (look == Look::RIGHT) sprite->SetAnimation((int)MedusaAnim::IDLE_RIGHT);

	visibility_area = area;

	InitPattern();

	return AppStatus::OK;
}
void Medusa::InitPattern()
{
	//Multiplying by 3 ensures sufficient time for displaying all 3 frames of the
	//walking animation, resulting in smoother transitions and preventing the animation
	//from appearing rushed or incomplete
	const int n = MEDUSA_ANIM_DELAY*2;

	//pattern.push_back({ {0, 0}, 2 * n, (int)MedusaAnim::IDLE_RIGHT });
	//pattern.push_back({ {MEDUSA_SPEED, 0}, n, (int)MedusaAnim::WALKING_RIGHT });
	//pattern.push_back({ {0, 0}, n, (int)MedusaAnim::IDLE_RIGHT });
	pattern.push_back({ {MEDUSA_SPEED,MEDUSA_SPEED}, n, (int)MedusaAnim::WALKING_RIGHT });
	pattern.push_back({ {MEDUSA_SPEED,-MEDUSA_SPEED}, n, (int)MedusaAnim::WALKING_RIGHT });
	pattern.push_back({ {MEDUSA_SPEED,MEDUSA_SPEED}, n, (int)MedusaAnim::WALKING_RIGHT });
	pattern.push_back({ {MEDUSA_SPEED,-MEDUSA_SPEED}, n, (int)MedusaAnim::WALKING_RIGHT });
	//pattern.push_back({ {0, 0}, n, (int)MedusaAnim::IDLE_RIGHT });
	
	//pattern.push_back({ {0, 0}, 2 * n, (int)MedusaAnim::IDLE_LEFT });
	//pattern.push_back({ {-MEDUSA_SPEED, 0}, n, (int)MedusaAnim::WALKING_LEFT });
	//pattern.push_back({ {0, 0}, n, (int)MedusaAnim::IDLE_LEFT });
	pattern.push_back({ {-MEDUSA_SPEED, MEDUSA_SPEED}, n, (int)MedusaAnim::WALKING_LEFT });
	pattern.push_back({ {-MEDUSA_SPEED, -MEDUSA_SPEED}, n, (int)MedusaAnim::WALKING_LEFT });
	pattern.push_back({ {-MEDUSA_SPEED, MEDUSA_SPEED}, n, (int)MedusaAnim::WALKING_LEFT });
	pattern.push_back({ {-MEDUSA_SPEED, -MEDUSA_SPEED}, n, (int)MedusaAnim::WALKING_LEFT });
	//pattern.push_back({ {0, 0}, n, (int)MedusaAnim::IDLE_LEFT });

	current_step = 0;
	current_frames = 0;
}
bool Medusa::Update(AABB& box)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	bool shoot = false;
	int anim_id;
	
	 if (cooldown == 0)
	  {
		state = MedusaState::ROAMING;
		counter = 300;
		cooldown = -1;
		
	  }
	if (box.pos.x <= pos.x)
	{
		look = Look::LEFT;
	}
	else 
	{
		look = Look::RIGHT;
	}
	if (state == MedusaState::ROAMING)
	{
		//if (IsVisible(box))
		//{
		//	//state = MedusaState::ATTACK;
		//	//The attack animation consists of 2 frames, with the second one being when
		//	//we throw the shot. Wait for a frame before initiating the attack.
		//	attack_delay = MEDUSA_ANIM_DELAY;

		//	if (look == Look::LEFT)	sprite->SetAnimation((int)MedusaAnim::ATTACK_LEFT);
		//	else					sprite->SetAnimation((int)MedusaAnim::ATTACK_RIGHT);
		//}


		/*if (box.pos.y +32 == pos.y)
		{
			state = MedusaState::ATTACK;
			cooldown = 120;
			if (look == Look::LEFT)	sprite->SetAnimation((int)MedusaAnim::ATTACK_LEFT);
			else					sprite->SetAnimation((int)MedusaAnim::ATTACK_RIGHT);


		}*/
		/*if (cooldown == 0)
		{*/
			pos += pattern[current_step].speed;


			current_frames++;

			if (current_frames == pattern[current_step].frames)
			{
				current_step++;
				current_step %= pattern.size();
				current_frames = 0;

				anim_id = pattern[current_step].anim;
				sprite->SetAnimation(anim_id);
				UpdateLook(anim_id);
			}
			attack_delay--;
			if (attack_delay == -1)
			{
				shoot = true;

				//The attack animation consists of 2 frames. Wait for a complete loop
				//before shooting again
				attack_delay = 2 * MEDUSA_ANIM_DELAY;
			}
			counter--;
		//}




	}
	else if (state == MedusaState::ATTACK)
	{
		if (look == Look::LEFT)	sprite->SetAnimation((int)MedusaAnim::ATTACK_LEFT);
			else					sprite->SetAnimation((int)MedusaAnim::ATTACK_RIGHT);
		cooldown--;
			//if (!IsVisible(box))
			//{
			//	state = MedusaState::ROAMING;

			//	//Continue with the previous animation pattern before initiating the attack
			//	anim_id = pattern[current_step].anim;
			//	sprite->SetAnimation(anim_id);
			//}
			//else
			//{
		
				//attack_delay--;
				//if (attack_delay == -1)
				//{
				//	shoot = true;

				//	//The attack animation consists of 2 frames. Wait for a complete loop
				//	//before shooting again
				//	attack_delay = 2 * MEDUSA_ANIM_DELAY;
				//}
			
	}

		//attack_delay--;
		//if (attack_delay == 0)
		//{
		//	shoot = true;

		//	//The attack animation consists of 2 frames. Wait for a complete loop
		//	//before shooting again
		//	attack_delay = 2 * MEDUSA_ANIM_DELAY;
		//}

	//attack_delay--;
	//if (attack_delay == -1)
	//{
	//	shoot = true;

	//	//The attack animation consists of 2 frames. Wait for a complete loop
	//	//before shooting again
	//	attack_delay = 2 * MEDUSA_ANIM_DELAY;
	//}
	if (counter == 0)
	{
		state = MedusaState::ATTACK;
		cooldown = 60;
		counter = -1;
	}
		sprite->Update();

		return shoot;
	}

void Medusa::UpdateLook(int anim_id)
{
	MedusaAnim anim = (MedusaAnim)anim_id;
	look = (anim == MedusaAnim::IDLE_LEFT ||
		anim == MedusaAnim::WALKING_LEFT ||
		anim == MedusaAnim::ATTACK_LEFT) ? Look::LEFT : Look::RIGHT;
}
void Medusa::GetShootingPosDir(Point* p, Point* d) const
{
	if (look == Look::LEFT)
	{
		p->x = pos.x + MEDUSA_SHOT_OFFSET_X_LEFT;
		*d = { -MEDUSA_SHOT_SPEED, 0 };
	}
	else
	{
		p->x = pos.x + MEDUSA_SHOT_OFFSET_X_RIGHT;
		*d = { MEDUSA_SHOT_SPEED, 0 };
	}
	p->y = pos.y + MEDUSA_SHOT_OFFSET_Y;
}