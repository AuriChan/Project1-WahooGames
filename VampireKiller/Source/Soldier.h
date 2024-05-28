#include "Enemy.h"
#define SOLDIER_SPEED			1
#define SOLDIER_ANIM_DELAY	(4*ANIM_DELAY)





enum class SlimeState { ROAMING, ATTACK };
enum class SlimeAnim {
	IDLE_LEFT, IDLE_RIGHT, WALKING_LEFT, WALKING_RIGHT,
	ATTACK_LEFT, ATTACK_RIGHT, NUM_ANIMATIONS
};

struct Step
{
	Point speed;	//direction
	int frames;		//duration in number of frames
	int anim;		//graphical representation
};

class Slime : public Enemy
{
public:
	Slime(const Point& p, int width, int height, int frame_width, int frame_height);
	~Slime();

	//Initialize the enemy with the specified look and area
	AppStatus Initialise(LookE look, const AABB& area) override;

	//Update the enemy according to its logic, return true if the enemy must shoot
	bool Update(const AABB& box) override;

	//Retrieve the position and direction of the shot to be thrown
	void GetShootingPosDir(Point* pos, Point* dir) const override;

private:
	//Create the pattern behaviour
	void InitPattern();

	//Update looking direction according to the current step of the pattern
	void UpdateLook(int anim_id);

	int attack_delay;	//delay between attacks
	SlimeState state;

	int current_step;	//current step of the pattern
	int current_frames;	//number of frames in the current step
	std::vector<Step> pattern;
};

