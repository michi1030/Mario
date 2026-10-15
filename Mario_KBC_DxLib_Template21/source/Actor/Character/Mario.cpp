#include "Mario.h"
#include "../../Input/InputManager.h"
#include "../../File/AssetContainer.h"
#include <DxLib.h>

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
	jump = 0;
	radius = 10.0f;
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
