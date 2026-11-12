#pragma once
#include <DxLib.h>
#include "../Actor.h"

class SuperStar : public Actor
{
private:
    float vx;
    float vy;
    float bouncePower;
    int width;
    int height;
    int state;
    float startY;
    float groundY;

    int imageHandle;   // AssetContainerから取得する単一ハンドル
    int animFrame;     // アニメーションカウント
    int currentFrame;  // 現在のコマ番号 (0〜3)

public:
    SuperStar();
    virtual ~SuperStar() override = default;

    virtual void Initialize() override;
    virtual void Update(float delta_second) override;
    virtual void Draw() const override;
    virtual void OnHitCollisionEnter(Actor* actor) override;
    virtual eActorTag GetActorTag() const override { return eActorTag::eItem_SuperStar; }

    void Spawn(float startX, float startYPos);
    void Deactivate();
};