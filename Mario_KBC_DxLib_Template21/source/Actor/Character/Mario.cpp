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
	speed = 120.0f;
	radius = 10.0f;
}

void Mario::Update(float delta_second)
{

}

void Mario::Finalize()
{

}
