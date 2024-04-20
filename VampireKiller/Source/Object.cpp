#include "Object.h"
#include "StaticImage.h"
#include "Sprite.h"

Object::Object(const Point& p, ObjectType t) : Entity(p, OBJECT_PHYSICAL_SIZE, OBJECT_PHYSICAL_SIZE, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE)
{
	type = t;

	Rectangle rc;
	const int n = TILE_SIZE;
	switch (type)
	{
	case ObjectType::APPLE: rc = { 4 * n, 3 * n, n, n }; break;
	case ObjectType::CHILI: rc = { 5 * n, 3 * n, n, n }; break;
	case ObjectType::HEART: rc = { 3 * n, 1 * n, n, n }; break;
	case ObjectType::THE_RING: rc = { 3 * n, 2 * n, n, n }; break;
	/*case ObjectType::FIRE: rc = { 5 * n, 3 * n, n, n }; break;*/

	default: LOG("Internal error: object creation of invalid type");
	}

	ResourceManager& data = ResourceManager::Instance();
	render = new StaticImage(data.GetTexture(Resource::IMG_ITEMS), rc);
	
}
Object::~Object()
{
}
ObjectType Object::GetType()
{
	return type;
};
void Object::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
}
int Object::Points() const
{
	if (type == ObjectType::APPLE)		return POINTS_APPLE;
	else if (type == ObjectType::CHILI)	return POINTS_CHILI;
	else if (type == ObjectType::HEART)	return POINTS_HEART;
	
	else
	{
		LOG("Internal error: object type invalid when giving points");
		return 0;
	}
}