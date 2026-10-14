
#pragma once

#include "../Actor.h"
#include "../../File/Sprite.h"

enum class eDirection : unsigned char
{
	eUp,
	eRight,
	eDown,
	eLeft,
	eNone,
};

class Character : public Actor
{
protected:
	Vector2 velocity;
	float speed;

public:
	Character();
	virtual ~Character();

protected:
	void Movement(float delta_second);

};
