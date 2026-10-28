#include "TitleScene.h"
#include "../File/AssetContainer.h"
#include "../Input/InputManager.h"
#include <DxLib.h>

TitleScene::TitleScene()
	: SceneBase()
	, font_handle(NULL)
	,title_image()
	, disp_timer(0.0f)
	, is_disp(true)
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	title_image = LoadGraph("assets/Images/title.png");
}

eSceneType TitleScene::Update(float delta_second)
{
	disp_timer += delta_second;
	if (disp_timer >= 0.5f)
	{
		disp_timer = 0.0f;
		is_disp = (not is_disp);
	}

	if (InputManager::GetKeyState(KEY_INPUT_SPACE) == eInputState::ePressed ||
		InputManager::GetButtonState(XINPUT_BUTTON_START) == eInputState::ePressed)
	{
		return eSceneType::eInGame;
	}

	return GetNowSceneType();
}

void TitleScene::Draw() const
{
	DrawRotaGraph(640, 360, 1, 0.0, title_image, TRUE);

	if (is_disp)
	{
		std::string disp_text = "== PUSH START BUTTON ==";
		int width = GetDrawStringWidthToHandle(disp_text.c_str(), (int)disp_text.size(), font_handle);
		DrawStringToHandle(336 - (width / 2), 432, disp_text.c_str(), GetColor(222, 222, 255), font_handle);
	}
}

void TitleScene::Finalize()
{
	DeleteFontToHandle(font_handle);
}

eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}