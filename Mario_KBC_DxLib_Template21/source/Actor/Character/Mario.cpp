#include "Mario.h"
#include "../../Input/InputManager.h"
#include "../../File/AssetContainer.h"
#include <DxLib.h>

#define D_GRAVITY 1500.0f

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
	speed = 10.0f;
	jump = 5;
	radius = 10.0f;
	star_mode = false;
	
}

void Mario::Update(float delta_second)
{
	InputCheck();
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

	//d—Í
	velocity.y += D_GRAVITY * delta_second;
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

void Mario::InputCheck()
{
	if (InputManager::GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::ePressed) 
	{
		velocity = -1;
	}
	else if (InputManager::GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eInputState::ePressed)
	{
		velocity = 1;
	}
	if (InputManager::GetButtonState(XINPUT_BUTTON_B) == eInputState::ePressed)
	{
		jump = 5;
	}
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
