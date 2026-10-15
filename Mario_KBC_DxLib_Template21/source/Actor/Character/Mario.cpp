#include "Mario.h"
#include "../../Input/InputManager.h"
#include "../../File/AssetContainer.h"

Mario::Mario()
	: Character()
	, animation_time()
	, animation_num()
{
	
}

Mario::~Mario()
{

}

void Mario::Initialize()
{
	AssetContainer* container = AssetContainer::Get();
	state = tibi;
	speed = 120.0f;
	radius = 10.0f;
}

void Mario::Update(float delta_second)
{
	switch (state)
	{
	case tibi:
		Tibi();
		break;
	case deka:
		Deka();
		break;
	case fire:
		Fire();
		break;
	default:
		break;
	}
}

void Mario::Finalize()
{

}

void Mario::OnHitCollisionEnter(Actor* actor)
{
	eActorTag tag = actor->GetActorTag();

	if (tag == eActorTag::eEnemy)
	{

	}
	else if (tag == eActorTag::eItem)
	{
		
	}
	else if (tag == eActorTag::eWall)
	{

	}
}

eActorTag Mario::GetActorTag() const
{
	return eActorTag::ePlayer;
}

void Mario::Tibi()
{

}

void Mario::Deka()
{

}

void Mario::Fire()
{

}
