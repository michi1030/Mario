#include "SuperStar.h"
#include "../../File/AssetContainer.h"

SuperStar::SuperStar()
    : Actor()
    , vx(2.0f)
    , vy(0.0f)
    , bouncePower(-8.0f)
    , width(32)
    , height(32)
    , state(0)
    , startY(0.0f)
    , groundY(600.0f)
    , imageHandle(-1)
    , animFrame(0)
    , currentFrame(0)
{
    radius = 16.0f;
}

void SuperStar::Initialize()
{
    // AssetContainer で画像を読み込み
    imageHandle = AssetContainer::Get()->GetImages("Item/star.png");
}

void SuperStar::Spawn(float startX, float startYPos)
{
    location.x = startX;
    location.y = startYPos;
    startY = startYPos;

    // 1秒あたりの移動速度・跳ね返り力（ピクセル/秒）に変更
    vx = 120.0f;           // 横移動速度
    vy = -240.0f;          // 初速
    bouncePower = -480.0f; // バウンドする強さ

    state = 0;
    actor_state = eActorState::eActive;
}

void SuperStar::Update(float delta_second)
{
    if (actor_state != eActorState::eActive) return;

    // アニメーションも時間ベースにすると安定します（約0.08秒ごとにコマ送り）
    static float animTimer = 0.0f;
    animTimer += delta_second;
    if (animTimer >= 0.08f)
    {
        animTimer = 0.0f;
        currentFrame = (currentFrame + 1) % 4;
    }

    if (state == 0)
    {
        // ブロックからせり上がる速度も delta_second を掛ける
        location.y -= 60.0f * delta_second;
        if (startY - location.y >= height)
        {
            state = 1;
        }
    }
    else if (state == 1)
    {
        // 横移動
        location.x += vx * delta_second;

        // 重力加速度（1秒あたりの落下加速）
        float gravity = 1500.0f;
        vy += gravity * delta_second;
        location.y += vy * delta_second;

        // 地面でのバウンド判定
        if (location.y + height >= groundY)
        {
            location.y = groundY - height;
            vy = bouncePower;
        }
    }
}

void SuperStar::Draw() const
{
    if (actor_state != eActorState::eActive || imageHandle == -1) return;

    // AssetContainerから取得した画像から、currentFrame番目のコマ(32x32)だけを切り抜いて描画
    DrawRectGraph(
        (int)location.x, (int)location.y, // 画面上の描画座標
        currentFrame * width, 0,          // 画像内の切り抜き開始座標 (X, Y)
        width, height,                    // 切り抜く幅・高さ (32, 32)
        imageHandle, TRUE, FALSE
    );
}

void SuperStar::OnHitCollisionEnter(Actor* actor)
{
    if (!actor) return;
    if (actor->GetActorTag() == eActorTag::ePlayer)
    {
        Deactivate();
        DestroyActor(this);
    }
}

void SuperStar::Deactivate()
{
    actor_state = eActorState::eDead;
}