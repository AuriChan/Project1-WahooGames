#include "Shot.h"
#include "StaticImage.h"

Shot::Shot()
{
	Rectangle rc = { 6 * TILE_SIZE + 4, 3*TILE_SIZE + 9, 7,7 };
	ResourceManager& data = ResourceManager::Instance();
	render = new StaticImage(data.GetTexture(ResourceImages::IMG_ENEMY), rc);

	SetAlive(false);
}
Shot::~Shot()
{
}
int Shot::GetDamage() const
{
	return damage;
}
void Shot::Init(const Point& p, const Point& dir)
{
	Set(p, dir, SHOT_PHYSICAL_WIDTH, SHOT_PHYSICAL_HEIGHT, SHOT_FRAME_WIDTH, SHOT_FRAME_HEIGHT);
}
bool Shot::IsMovingLeft() const
{
	return dir.x < 0;
}
bool Shot::IsMovingRight() const
{
	return dir.x > 0;
}
void Shot::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
}
