#pragma once

#include "../Character.h"

class Kuribo : public Character
{
private:
	DivSprite* move_animation;
	float animation_time;
	int animation_num;
	int move_direction; // -1: ç∂, 1: âE
	bool is_crushed;    // ì•Ç‹ÇÍÇΩÇ©
	float delete_timer; // ì•Ç‹ÇÍÇƒÇ©ÇÁè¡Ç¶ÇÈÇ‹Ç≈ÇÃéûä‘

public:
	Kuribo();
	Kuribo(const Vector2& spawn_pos);
	virtual ~Kuribo();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Finalize() override;
	virtual eActorTag GetActorTag() const override;
	virtual void OnHitCollisionEnter(Actor* actor) override;

	void Crush();
};