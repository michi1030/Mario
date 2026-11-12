#include "FireFlower.h"
#include "../../File/AssetContainer.h"
#include "../../File/Sprite.h"

FireFlower::FireFlower()
    : Actor()
    , width(32)
    , height(32)
    , state(0)
    , startY(0.0f)
    , animFrame(0)
    , currentFrame(0)
{
    radius = 16.0f;
    for (int i = 0; i < 4; ++i)
    {
        imageHandles[i] = -1;
    }
}

void FireFlower::Initialize()
{
    // AssetContainer / DivSprite を経由して分割スプライトを取得
    DivSprite sprite("Item/flower.png", 4, 1);
    for (int i = 0; i < 4 && i < sprite.GetSize(); ++i)
    {
        imageHandles[i] = sprite[i]; // int型のハンドルを取り出して配列に格納
    }
}

void FireFlower::Spawn(float startX, float startYPos)
{
    location.x = startX;
    location.y = startYPos;
    startY = startYPos;
    state = 0;
    actor_state = eActorState::eActive;
}

void FireFlower::Update(float delta_second)
{
    if (actor_state != eActorState::eActive) return;

    // パラパラアニメーション (4コマを順に切り替え)
    animFrame++;
    if (animFrame >= 8)
    {
        animFrame = 0;
        currentFrame = (currentFrame + 1) % 4;
    }

    if (state == 0)
    {
        location.y -= 1.0f;
        if (startY - location.y >= height)
        {
            state = 1;
        }
    }
}

void FireFlower::Draw() const
{
    if (actor_state != eActorState::eActive || imageHandles[currentFrame] == -1) return;

    // int 配列の指定コマを描画
    DrawGraph((int)location.x, (int)location.y, imageHandles[currentFrame], TRUE);
}

void FireFlower::OnHitCollisionEnter(Actor* actor)
{
    if (!actor) return;
    if (actor->GetActorTag() == eActorTag::ePlayer)
    {
        Deactivate();
        DestroyActor(this);
    }
}

void FireFlower::Deactivate()
{
    actor_state = eActorState::eDead;
}