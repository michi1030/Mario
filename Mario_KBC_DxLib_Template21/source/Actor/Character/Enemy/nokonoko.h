#pragma once

#include "../Character.h"

enum class eNokonokoState : unsigned char
{
	eWalk,      // 通常歩行
	eShellStop, // 甲羅（静止・復活カウント中）
	eShellSpin, // 甲羅（高速滑走）
};

class Nokonoko : public Character
{
private:
	DivSprite* walk_animation;  // Enemy/nokonoko.png (2x1)
	DivSprite* shell_animation; // Enemy/nokonoko_revival.png (2x1)
	eNokonokoState state;
	float animation_time;
	int animation_num;
	float revival_timer; // 甲羅になってからの経過時間
	float walk_speed;
	float shell_speed;
	int move_direction; // -1: 左, 1: 右

public:
	Nokonoko();
	Nokonoko(const Vector2& spawn_pos);
	virtual ~Nokonoko();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Finalize() override;
	virtual eActorTag GetActorTag() const override;
	virtual void OnHitCollisionEnter(Actor* actor) override;

	void OnStomped(float player_x);
};