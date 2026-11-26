#include "kuribo-.h"
#include "../../../File/StageData.h" // ※環境に合わせてパスを調整してください
#include <DxLib.h>

#define D_GRAVITY 1000.0f

static bool IsSolidPanel(ePanelID id)
{
	switch (id)
	{
	case ePanelID::eWall:
	case ePanelID::eBranch:
	case ePanelID::eGate:
	case ePanelID::eBlock:
	case ePanelID::eHardBlock:
	case ePanelID::eHatena:
	case ePanelID::eDokan_a:
	case ePanelID::eDokan_b:
	case ePanelID::eDokan_c:
	case ePanelID::eDokan_d:
	case ePanelID::eFort:
		return true;
	default:
		return false;
	}
}

static bool CheckStageSolid(float wx, float wy)
{
	const float draw_chip_size = 768.0f / 14.0f;
	int gx = static_cast<int>(wx / draw_chip_size);
	int gy = static_cast<int>(wy / draw_chip_size);

	if (gy < 0 || gy >= 14 || gx < 0)
	{
		return false;
	}

	const auto& map = StageData::Get()->GetAll();
	if (gy >= static_cast<int>(map.size()) || gx >= static_cast<int>(map[gy].size()))
	{
		return false;
	}

	return IsSolidPanel(map[gy][gx]);
}

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

	const float draw_chip_size = 768.0f / 14.0f;
	int w = 0, h = 0;
	GetGraphSize(image, &w, &h);
	float half_w = (w * 0.5f) * static_cast<float>(scale);
	float half_h = (h * 0.5f) * static_cast<float>(scale);

	// 1. 横移動と壁・土管の当たり判定
	velocity.x = static_cast<float>(move_direction);
	location.x += velocity.x * speed * delta_second;

	// 足元の床に引っかからないよう、上下少し内側の2点で壁チェック
	float check_top = location.y - half_h * 0.6f;
	float check_bottom = location.y + half_h * 0.6f;

	if (move_direction < 0)
	{
		float left_edge = location.x - half_w;
		if (CheckStageSolid(left_edge, check_top) || CheckStageSolid(left_edge, check_bottom))
		{
			int gx = static_cast<int>(left_edge / draw_chip_size);
			location.x = (gx + 1) * draw_chip_size + half_w;
			move_direction = 1;
			direction = TRUE;
		}
	}
	else if (move_direction > 0)
	{
		float right_edge = location.x + half_w;
		if (CheckStageSolid(right_edge, check_top) || CheckStageSolid(right_edge, check_bottom))
		{
			int gx = static_cast<int>(right_edge / draw_chip_size);
			location.x = gx * draw_chip_size - half_w;
			move_direction = -1;
			direction = FALSE;
		}
	}

	// 2. 重力・縦移動と床・穴の当たり判定
	velocity.y += D_GRAVITY * delta_second;
	location.y += velocity.y * delta_second;

	// 横の壁に誤反応しないよう、左右少し内側の2点で足元チェック
	float foot_y = location.y + half_h;
	float foot_left = location.x - half_w * 0.7f;
	float foot_right = location.x + half_w * 0.7f;

	if (velocity.y >= 0.0f && (CheckStageSolid(foot_left, foot_y) || CheckStageSolid(foot_right, foot_y)))
	{
		int gy = static_cast<int>(foot_y / draw_chip_size);
		location.y = gy * draw_chip_size - half_h;
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
	if (tag == eActorTag::eWall || tag == eActorTag::eEnemy)
	{
		// 壁や他の敵に当たったら反転
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