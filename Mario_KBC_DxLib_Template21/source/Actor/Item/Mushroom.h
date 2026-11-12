// Mushroom.h
#pragma once
#include <DxLib.h>
#include "../Actor.h"

class Mushroom : public Actor
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
    Mushroom();
    virtual ~Mushroom() override = default;

    virtual void Initialize() override;
    virtual void Update(float delta_second) override;
    virtual void Draw() const override;
    virtual void OnHitCollisionEnter(Actor* actor) override;
    virtual eActorTag GetActorTag() const override { return eActorTag::eItem_Mushroom; }

    void Spawn(float startX, float startYPos);
    void Deactivate();
};