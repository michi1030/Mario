#pragma once
<<<<<<< HEAD

#include "SceneBase.h"
#include "../File/Sprite.h"

class TitleScene : public SceneBase
{
private:
	int font_handle;
	int title_image;
	float disp_timer;
	bool is_disp;

public:
	TitleScene();
	virtual ~TitleScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update(float delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

};
=======
>>>>>>> upstream/main
