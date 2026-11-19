#include "kuribo-.h"
#include <DxLib.h>

#define D_GRAVITY 1000.0f

Kuribo::Kuribo()
	: Character()
	, move_animation(nullptr)
	, animation_time(0.0f)
	, animation_num(0)
	, move_direction(-1)
	, is_crushed(false)
	, delete_timer(0.0f)
{
}

Kuribo::Kuribo(const Vector2& spawn_pos)
	: Kuribo()
{
	location = spawn_pos;
}

Kuribo::~Kuribo()
{
	Finalize();
}

void Kuribo::Initialize()
{
	speed = 60.0f;
	radius = 10.0f;
	direction = FALSE; // 左向き

	move_animation = new DivSprite("Enemy/kuribo.png", 3, 1);
	if (move_animation != nullptr)
	{
		image = (*move_animation)[0];

		// 画像の横幅を取得して、ステージの1マス（draw_chip_size）と同じ大きさに自動調整
		int w = 0, h = 0;
		GetGraphSize(image, &w, &h);
		if (w > 0)
		{
			scale = (768.0f / 14.0f) / static_cast<double>(w);
		}
	}
}

void Kuribo::Update(float delta_second)
{
	// 踏まれて潰れた後
	if (is_crushed)
	{
		delete_timer += delta_second;
		if (delete_timer >= 0.5f)
		{
			// 削除フラグがあればここで立てる（例: is_dead = true;）
		}
		return;
	}

	// 横移動（Character::Movement に合わせて速度ベクトルを設定）
	velocity.x = static_cast<float>(move_direction);
	location.x += velocity.x * speed * delta_second;

	// 重力と縦移動
	velocity.y += D_GRAVITY * delta_second;
	location.y += velocity.y * delta_second;

	// 仮地面（StageDataとの当たり判定実装までの仮処理）
	if (location.y >= 630.8f)
	{
		location.y = 630.8f;
		velocity.y = 0.0f;
	}

	// 歩行アニメーション（0番と1番を交互に切り替え）
	if (move_animation != nullptr)
	{
		animation_time += delta_second;
		if (animation_time >= 0.2f)
		{
			animation_num = (animation_num == 0) ? 1 : 0;
			image = (*move_animation)[animation_num];
			animation_time = 0.0f;
		}
	}
}

void Kuribo::Finalize()
{
	if (move_animation != nullptr)
	{
		delete move_animation;
		move_animation = nullptr;
	}
}

eActorTag Kuribo::GetActorTag() const
{
	return eActorTag::eEnemy;
}

void Kuribo::OnHitCollisionEnter(Actor* actor)
{
	if (actor == nullptr || is_crushed) return;

	eActorTag tag = actor->GetActorTag();
	if (tag == eActorTag::eWall)
	{
		// 壁に当たったら反転
		move_direction *= -1;
		direction = (move_direction > 0) ? TRUE : FALSE;
	}
}

void Kuribo::Crush()
{
	is_crushed = true;
	velocity = Vector2(0.0f, 0.0f);
	if (move_animation != nullptr)
	{
		image = (*move_animation)[2]; // 潰れ画像
	}
}