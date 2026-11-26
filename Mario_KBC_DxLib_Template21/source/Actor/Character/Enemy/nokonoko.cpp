#include "nokonoko.h"
#include "../../../File/StageData.h" // ※環境に合わせてパスを調整してください
#include <DxLib.h>

#define D_GRAVITY 1000.0f
#define D_REVIVAL_TIME 5.0f // 甲羅から復活するまでの秒数
#define D_WARNING_TIME 3.0f // 脚を出し始める秒数

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

Nokonoko::Nokonoko()
	: Character()
	, walk_animation(nullptr)
	, shell_animation(nullptr)
	, state(eNokonokoState::eWalk)
	, animation_time(0.0f)
	, animation_num(0)
	, revival_timer(0.0f)
	, walk_speed(60.0f)
	, shell_speed(350.0f)
	, move_direction(-1)
{
}

Nokonoko::Nokonoko(const Vector2& spawn_pos)
	: Nokonoko()
{
	location = spawn_pos;
}

Nokonoko::~Nokonoko()
{
	Finalize();
}

void Nokonoko::Initialize()
{
	speed = walk_speed;
	radius = 10.0f;
	direction = FALSE; // 左向き

	walk_animation = new DivSprite("Enemy/nokonoko.png", 2, 1);
	shell_animation = new DivSprite("Enemy/nokonoko_revival.png", 2, 1);

	if (walk_animation != nullptr)
	{
		image = (*walk_animation)[0];

		int w = 0, h = 0;
		GetGraphSize(image, &w, &h);
		if (w > 0)
		{
			scale = (768.0f / 14.0f) / static_cast<double>(w);
			location.y -= ((h - w) * 0.5f) * static_cast<float>(scale);
		}
	}
}

void Nokonoko::Update(float delta_second)
{
	// 状態に応じたスピード設定
	if (state == eNokonokoState::eWalk)
	{
		speed = walk_speed;
	}
	else if (state == eNokonokoState::eShellSpin)
	{
		speed = shell_speed;
	}
	else
	{
		speed = 0.0f;
	}

	const float draw_chip_size = 768.0f / 14.0f;
	int w = 0, h = 0;
	GetGraphSize(image, &w, &h);
	float half_w = (w * 0.5f) * static_cast<float>(scale);
	float half_h = (h * 0.5f) * static_cast<float>(scale);

	// 1. 横移動と壁・土管の当たり判定
	velocity.x = static_cast<float>(move_direction);
	location.x += velocity.x * speed * delta_second;

	if (speed > 0.0f)
	{
		// 床ブロックに誤反応しないよう、体の中心〜少し上あたりで壁をチェックする
		float check_top = location.y - half_h * 0.3f;
		float check_bottom = location.y + half_h * 0.2f;

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
	}

	// 2. 重力・縦移動と床・穴の当たり判定
	velocity.y += D_GRAVITY * delta_second;
	location.y += velocity.y * delta_second;

	float foot_y = location.y + half_h;
	float foot_left = location.x - half_w * 0.7f;
	float foot_right = location.x + half_w * 0.7f;

	if (velocity.y >= 0.0f && (CheckStageSolid(foot_left, foot_y) || CheckStageSolid(foot_right, foot_y)))
	{
		int gy = static_cast<int>(foot_y / draw_chip_size);
		location.y = gy * draw_chip_size - half_h;
		velocity.y = 0.0f;
	}

	// 3. 状態ごとのアニメーション・タイマー更新
	if (state == eNokonokoState::eWalk)
	{
		if (walk_animation != nullptr)
		{
			animation_time += delta_second;
			if (animation_time >= 0.25f)
			{
				animation_num = (animation_num == 0) ? 1 : 0;
				image = (*walk_animation)[animation_num];
				animation_time = 0.0f;
			}
		}
	}
	else if (state == eNokonokoState::eShellStop)
	{
		revival_timer += delta_second;

		if (revival_timer >= D_REVIVAL_TIME)
		{
			state = eNokonokoState::eWalk;
			revival_timer = 0.0f;
			animation_num = 0;
			animation_time = 0.0f;
			if (walk_animation != nullptr)
			{
				image = (*walk_animation)[0];
				// 甲羅から歩行に戻って背が高くなる分、床にめり込まないよう上に補正
				int new_w = 0, new_h = 0;
				GetGraphSize(image, &new_w, &new_h);
				float new_half_h = (new_h * 0.5f) * static_cast<float>(scale);
				location.y -= (new_half_h - half_h);
			}
			return;
		}

		if (shell_animation != nullptr)
		{
			if (revival_timer >= D_WARNING_TIME)
			{
				animation_time += delta_second;
				if (animation_time >= 0.15f)
				{
					animation_num = (animation_num == 0) ? 1 : 0;
					image = (*shell_animation)[animation_num];
					animation_time = 0.0f;
				}
			}
			else
			{
				image = (*shell_animation)[0];
			}
		}
	}
	else if (state == eNokonokoState::eShellSpin)
	{
		if (shell_animation != nullptr)
		{
			image = (*shell_animation)[0];
		}
	}
}

void Nokonoko::Finalize()
{
	if (walk_animation != nullptr)
	{
		delete walk_animation;
		walk_animation = nullptr;
	}
	if (shell_animation != nullptr)
	{
		delete shell_animation;
		shell_animation = nullptr;
	}
}

eActorTag Nokonoko::GetActorTag() const
{
	return eActorTag::eEnemy;
}

void Nokonoko::OnHitCollisionEnter(Actor* actor)
{
	if (actor == nullptr) return;

	eActorTag tag = actor->GetActorTag();
	if (tag == eActorTag::eWall || tag == eActorTag::eEnemy)
	{
		// 甲羅滑走中（eShellSpin）は反転せず突き進むようにするなら != eShellSpin を条件にする
		if (state != eNokonokoState::eShellSpin)
		{
			move_direction *= -1;
			direction = (move_direction > 0) ? TRUE : FALSE;
		}
	}
}

void Nokonoko::OnStomped(float player_x)
{
	if (state == eNokonokoState::eWalk)
	{
		state = eNokonokoState::eShellStop;
		revival_timer = 0.0f;
		animation_num = 0;
		animation_time = 0.0f;
	}
	else if (state == eNokonokoState::eShellStop)
	{
		state = eNokonokoState::eShellSpin;
		revival_timer = 0.0f;
		move_direction = (location.x >= player_x) ? 1 : -1;
		direction = (move_direction > 0) ? TRUE : FALSE;
	}
	else if (state == eNokonokoState::eShellSpin)
	{
		state = eNokonokoState::eShellStop;
		revival_timer = 0.0f;
		animation_num = 0;
		animation_time = 0.0f;
	}
}