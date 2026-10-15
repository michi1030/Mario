#pragma once
#include "Character.h"
#include <vector>

enum eState
{
	tibi,
	deka,
	fire,
};

class Mario : public Character
{
private:
	float animation_time;
	int animation_num;
	eState state;
	int level;

public:
	Mario();
	virtual ~Mario();
	
public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Finalize() override;

public:
	virtual void OnHitCollisionEnter(Actor* actor) override;
	eActorTag GetActorTag() const override;

private:
	void Tibi();
	void Deka();
	void Fire();

};
