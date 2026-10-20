#pragma once

#include"SceneBase.h"
#include"../Actor/Actor.h"
#include"../File/Sprite.h"

#include<vector>
#include<stdexcept>

/// <summary>
/// インゲーム画面
/// </summary>
class InGameScene :public SceneBase
{
private:
	/// <summary>
	/// ゲームの状態設定
	/// </summary>
	enum eGameState :unsigned char
	{
		ePlay,//待機
		ePause,//遊ぶ
		eResult,//リザルト遷移
	};

private:

public:
	InGameScene();
	virtual ~InGameScene();

public:
	virtual void Initialize() override;
	virtual eSceneType Update(float delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowSceneType() const override;

private:
	void LoadStageData();//ステージ読み込み
	void ChangeGameState(eGameState new_state);//ゲーム状態の変更
	void PlayUpdate(float delta_second);//遊んでいる最中の更新処理
	void CheckCollision();//当たり判定を行う

public:
	
	
};
