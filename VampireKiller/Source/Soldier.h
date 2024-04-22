#include "Enemy.h"


enum class SoldierState{ WALKING_LEFT, WALKING_RIGHT, STILL};
enum class SoldierAnim{WALKING_RIGHT, WALKING_LEFT, IDLE};

struct Step
{
	Point speed;	//direction
	int frames;		//duration in number of frames
	int anim;		//graphical representation
};
class Soldier : public Enemy
{
public:
private:
	Point pos;

};