#include"InGameScene.h"
#include"../File/AssetContainer.h"
#include"../File/StageData.h"
#include"../Input/InputManager.h"

#include"../Actor/Character/Mario.h"
#include"../Actor/Character/Enemy/kuribo-.h"
#include"../Actor/Character/Enemy/nokonoko.h"
#include"../Actor/Item/1up.h"
#include"../Actor/Item/fire.h"
#include"../Actor/Item/kinoko.h"
#include"../Actor/Item/star.h"

#include <DxLib.h>
#include <fstream>
#include <sstream>

InGameScene::InGameScene()
    :SceneBase()
    ,player(nullptr)
    ,enemy(nullptr)
    ,font_handle(NULL)
{

}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{

}

eSceneType InGameScene::Update(float delta_second)
{

}

void InGameScene::Draw() const
{

}

void InGameScene::Finalize()
{

}

eSceneType InGameScene::GetNowSceneType() const
{

}

void InGameScene::LoadStageData()
{

}

void InGameScene::ChangeGameState(eGameState new_state)
{

}

void InGameScene::PlayUpdate(float delta_second)
{

}

void InGameScene::CheckCollision()
{

}