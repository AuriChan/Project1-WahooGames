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
	case ObjectType::MORNINGSTAR_WHIP: rc = { 0, 0, n, n }; break;
	case ObjectType::BATTLE_CROSS: rc = { n, 0, n, n }; break;
	case ObjectType::HOURGLASS: rc = { 2 * n, 0, n, n }; break;
	case ObjectType::HOLY_WATER: rc = { 3 * n, 0, n, n }; break;
	case ObjectType::MAGIC_STAFF: rc = { 4 * n, 0, n, n }; break;
	case ObjectType::BOSS_ORB: rc = { 5 * n, 0, n, n }; break;
	case ObjectType::INVULNERABILITY_ORB: rc = { 7 * n, 0, n, n }; break;
	case ObjectType::ITEM_CHEST: rc = { 0, n, n, n }; break;
	case ObjectType::CHEST1: rc = { 0, n, n, n }; break;
	case ObjectType::CHEST2: rc = { 0, n, n, n }; break;
	case ObjectType::CHEST3: rc = { 0, n, n, n }; break;
	case ObjectType::CHEST4: rc = { 0, n, n, n }; break;
	case ObjectType::CHEST5: rc = { 0, n, n, n }; break;
	case ObjectType::GOLD_KEY: rc = { n, n, n, n }; break;
	case ObjectType::TKEY_1: rc = { n, n, n, n }; break;
	case ObjectType::TKEY_2: rc = { n, n, n, n }; break;
	case ObjectType::TKEY_3: rc = { n, n, n, n }; break;
	case ObjectType::TKEY_4: rc = { n, n, n, n }; break;
	case ObjectType::TKEY_5: rc = { n, n, n, n }; break;
	case ObjectType::SILVER_KEY: rc = { 2 * n, n, n, n }; break;
	case ObjectType::HEART: rc = { 3 * n, n, n, n }; break;
	case ObjectType::SPEED_BOOTS: rc = { 0, 2 * n, n, n }; break;
	case ObjectType::SHIELD_A: rc = { n, 2 * n, n, n }; break;
	case ObjectType::SHIELD_B: rc = { 2 * n, 2 * n, n, n }; break;
	case ObjectType::THE_RING: rc = { 3 * n, 2 * n, n, n }; break;
	case ObjectType::BLACK_BIBLE: rc = { 4 * n, 2 * n, n, n }; break;
	case ObjectType::WHITE_BIBLE: rc = { 5 * n, 2 * n, n, n }; break;
	case ObjectType::WINGS: rc = { 6 * n, 2 * n, n, n }; break;
	case ObjectType::SILVER_CROSS: rc = { 7 * n, 2 * n, n, n }; break;
	case ObjectType::WHITE_MONEY_BAG: rc = { 0 , 3 * n, n, n }; break;
	case ObjectType::BLUE_MONEY_BAG: rc = { n, 3 * n, n, n }; break;
	case ObjectType::STAGE_MAP: rc = { 2 * n, 3 * n, n, n }; break;
	case ObjectType::HEALTH_ORB: rc = { 3 * n, 3 * n, n, n }; break;
	case ObjectType::GOLD_CROSS: rc = { 4 * n, 3 * n, n, n }; break;

	default: LOG("Internal error: object creation of invalid type");
	}

	ResourceManager& data = ResourceManager::Instance();
	render = new StaticImage(data.GetTexture(ResourceImages::IMG_ITEMS), rc);
	
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
	
	if (type == ObjectType::HEART)	return POINTS_HEART;
	
	else
	{
		LOG("Internal error: object type invalid when giving points");
		return 0;
	}
}