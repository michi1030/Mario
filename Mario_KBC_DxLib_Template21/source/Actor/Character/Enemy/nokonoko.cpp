#include "nokonoko.h"
#include <DxLib.h>

#define D_GRAVITY 1000.0f
#define D_REVIVAL_TIME 5.0f // 甲羅から復活するまでの秒数
#define D_WARNING_TIME 3.0f // 脚を出し始める秒数

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
			// 横幅をステージの1マス（draw_chip_size）と同じ大きさに自動調整
			scale = (768.0f / 14.0f) / static_cast<double>(w);

			// 縦幅(h)から横幅1マス分(w)を引いた半分 × scale だけ上にずらして足元を地面に揃える
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

	// 横移動
	velocity.x = static_cast<float>(move_direction);
	location.x += velocity.x * speed * delta_second;

	// 重力と縦移動
	velocity.y += D_GRAVITY * delta_second;
	location.y += velocity.y * delta_second;

	// Nokonoko::Update() 内の仮地面処理
	const float draw_chip_size = 768.0f / 14.0f;
	// 床ブロック（下から2マス＝y=12, 13）の上面のY座標
	const float floor_top_y = draw_chip_size * 12.0f;

	// ノコノコの画像の半分の高さ分だけ上を中心にする
	int w = 0, h = 0;
	GetGraphSize(image, &w, &h);
	float half_height = (h * 0.5f) * static_cast<float>(scale);

	if (location.y + half_height >= floor_top_y)
	{
		location.y = floor_top_y - half_height;
		velocity.y = 0.0f;
	}

	// 状態ごとのアニメーション・タイマー更新
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

		// 一定時間経過で歩行状態に復活
		if (revival_timer >= D_REVIVAL_TIME)
		{
			state = eNokonokoState::eWalk;
			revival_timer = 0.0f;
			animation_num = 0;
			animation_time = 0.0f;
			if (walk_animation != nullptr)
			{
				image = (*walk_animation)[0];
			}
			return;
		}

		if (shell_animation != nullptr)
		{
			if (revival_timer >= D_WARNING_TIME)
			{
				// 復活直前：甲羅(0)と脚出し(1)を交互に切り替え
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
				// 通常の甲羅静止
				image = (*shell_animation)[0];
			}
		}
	}
	else if (state == eNokonokoState::eShellSpin)
	{
		// 高速滑走中は甲羅(0)固定
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
	if (tag == eActorTag::eWall)
	{
		move_direction *= -1;
		direction = (move_direction > 0) ? TRUE : FALSE;
	}
}

void Nokonoko::OnStomped(float player_x)
{
	if (state == eNokonokoState::eWalk)
	{
		// 歩行 → 甲羅静止
		state = eNokonokoState::eShellStop;
		revival_timer = 0.0f;
		animation_num = 0;
		animation_time = 0.0f;
	}
	else if (state == eNokonokoState::eShellStop)
	{
		// 甲羅静止 → マリオの位置と逆方向へ高速滑走
		state = eNokonokoState::eShellSpin;
		revival_timer = 0.0f;
		move_direction = (location.x >= player_x) ? 1 : -1;
		direction = (move_direction > 0) ? TRUE : FALSE;
	}
	else if (state == eNokonokoState::eShellSpin)
	{
		// 滑走中に踏まれたら再び停止
		state = eNokonokoState::eShellStop;
		revival_timer = 0.0f;
		animation_num = 0;
		animation_time = 0.0f;
	}
}