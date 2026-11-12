// OneUpMushroom.cpp
#include "OneUpMushroom.h"
#include "../../File/AssetContainer.h"

OneUpMushroom::OneUpMushroom()
    : Actor()
    , vx(1.5f)
    , vy(0.0f)
    , width(32)
    , height(32)
    , state(0)
    , startY(0.0f)
    , groundY(600.0f)
    , imageHandle(-1)
{
    radius = 16.0f;
}

void OneUpMushroom::Initialize()
{
    imageHandle = AssetContainer::Get()->GetImages("Item/1up_mushroom.png");
}

void OneUpMushroom::Spawn(float startX, float startYPos)
{
    location.x = startX;
    location.y = startYPos;
    startY = startYPos;
    vx = 1.5f;
    vy = 0.0f;
    state = 0;
    actor_state = eActorState::eActive;
}

void OneUpMushroom::Update(float delta_second)
{
    if (actor_state != eActorState::eActive) return;

    if (state == 0)
    {
        location.y -= 1.0f;
        if (startY - location.y >= height)
        {
            state = 1;
        }
    }
    else if (state == 1)
    {
        location.x += vx;

        vy += 0.5f;
        location.y += vy;

        if (location.y + height >= groundY)
        {
            location.y = groundY - height;
            vy = 0.0f;
        }
    }
}

void OneUpMushroom::Draw() const
{
    if (actor_state != eActorState::eActive || imageHandle == -1) return;
    DrawGraph((int)location.x, (int)location.y, imageHandle, TRUE);
}

void OneUpMushroom::OnHitCollisionEnter(Actor* actor)
{
    if (!actor) return;
    if (actor->GetActorTag() == eActorTag::ePlayer)
    {
        Deactivate();
        DestroyActor(this);
    }
}

void OneUpMushroom::Deactivate()
{
    actor_state = eActorState::eDead;
}