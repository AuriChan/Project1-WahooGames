#pragma once
#include "Entity.h"

#define OBJECT_PHYSICAL_SIZE	14
#define OBJECT_FRAME_SIZE		16

#define POINTS_APPLE	10
#define POINTS_CHILI	20
#define POINTS_HEART	1

enum class ObjectType { APPLE, CHILI, MORNINGSTAR_WHIP, BATTLE_CROSS, HOURGLASS, HOLY_WATER, MAGIC_STAFF, 
	BOSS_ORB, INVULNERABILITY_ORB, ITEM_CHEST, GOLD_KEY, SILVER_KEY, HEART, SPEED_BOOTS, SHIELD_A, SHIELD_B,
	THE_RING, BLACK_BIBLE, WHITE_BIBLE, WINGS, SILVER_CROSS, WHITE_MONEY_BAG, BLUE_MONEY_BAG, STAGE_MAP,
	HEALTH_ORB, GOLD_CROSS};

class Object : public Entity
{
public:
	Object(const Point& p, ObjectType t);
	~Object();

	void DrawDebug(const Color& col) const;
	int Points() const;
	ObjectType GetType();

private:
	ObjectType type;
};
