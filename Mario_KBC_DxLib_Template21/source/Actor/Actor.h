#pragma once

#include "../Utility/Math/Vector2.h"

enum class eActorState : unsigned char
{
	eActive = 0,
	ePaused,
	eDead,
};

enum class eActorTag : unsigned char
{
	eNone,
	ePlayer,
	eEnemy,
	eWall,
	eItem,
};

class Actor
{
protected:
	Vector2 location;
	float radius;
	int image;
	double scale;
	unsigned char z_layer;
	bool is_destroy;
	eActorState actor_state;

public:
	Actor();
	virtual ~Actor();

public:
	virtual void Initialize();
	virtual void Update(float delta_second);
	virtual void Draw() const;
	virtual void Finalize();

public:
	virtual void OnHitCollisionEnter(Actor* actor);
	virtual eActorTag GetActorTag() const = 0;

public:
	const Vector2& GetLocation() const;
	float GetRadius() const;
	eActorState GetState() const;
	unsigned char GetZLayer() const;
	void SetLocation(const Vector2& location);

protected:
	void DestroyActor(Actor* target = nullptr);

};
