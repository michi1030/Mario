#pragma once
#include <DxLib.h>
#include "../Actor.h"
#include <vector>

class FireFlower : public Actor
{
private:
    int width;
    int height;
    int state;
    float startY;

    int imageHandles[4];
    int animFrame;
    int currentFrame;

public:
    FireFlower();
    virtual ~FireFlower() override = default;

    virtual void Initialize() override;
    virtual void Update(float delta_second) override;
    virtual void Draw() const override;
    virtual void OnHitCollisionEnter(Actor* actor) override;
    virtual eActorTag GetActorTag() const override { return eActorTag::eItem_FireFlower; }

    void Spawn(float startX, float startYPos);
    void Deactivate();
};