// OneUpMushroom.h
#pragma once
#include <DxLib.h>
#include "../Actor.h"

class OneUpMushroom : public Actor
{
private:
    float vx;
    float vy;
    int width;
    int height;
    int state;
    float startY;
    float groundY;
    int imageHandle;

public:
    OneUpMushroom();
    virtual ~OneUpMushroom() override = default;

    virtual void Initialize() override;
    virtual void Update(float delta_second) override;
    virtual void Draw() const override;
    virtual void OnHitCollisionEnter(Actor* actor) override;
    virtual eActorTag GetActorTag() const override { return eActorTag::eItem_OneUpMushroom; }

    void Spawn(float startX, float startYPos);
    void Deactivate();
};