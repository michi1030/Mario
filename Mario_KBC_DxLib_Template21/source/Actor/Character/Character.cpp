#include "Character.h"

Character::Character()
	: Actor()
	, velocity()
	, speed(0.0f)
{

}

Character::~Character()
{

}

void Character::Movement(float delta_second)
{
	location += velocity * speed * delta_second;
}
