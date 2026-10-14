#pragma once
#include "Character.h"
#include <vector>

class Mario : public Character
{
private:
	float animation_time;
	int animation_num;

public:
	Mario();
	virtual ~Mario();
	
public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Finalize() override;

};
