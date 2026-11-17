#include "ResultScene.h"
#include "../File/Sprite.h"
#include "../Input/InputManager.h"
#include <DxLib.h>

/**
 * @brief コンストラクタ
 * @details メンバ変数の初期化を行います。
 */
ResultScene::ResultScene()
	: SceneBase()
	, time_image(nullptr)
	, world_image(nullptr)
	, stage_number(nullptr)
	, mario_image(nullptr)
	, mario_stock(nullptr)
	, mario_name(nullptr)
	, score_image(nullptr)
	, coin_image(nullptr)
	, coin_count(0)
	, score(0)
	, font_handle(NULL)
	, blink_time(0.0f)
	, is_blink(true)
{
	// 処理なし
}

/**
 * @brief デストラクタ
 */
ResultScene::~ResultScene()
{
	// 処理なし
}

/**
 * @brief 初期化処理
 * @details リザルト画面で使用する画像やフォントなどのリソースを読み込みます。
 */
void ResultScene::Initialize()
{
	coin_count = 10;
	stock = 3;
	score = 123456;
	mario_image = new DivSprite("Mario/mario.png", 9, 1);
	mario_stock = new DivSprite("UI/num.png", 15, 1);
	mario_name = new DivSprite("UI/name_mario.png", 1, 1);
	coin_image = new DivSprite("UI/uicoin.png", 4, 1);
	world_image = new Sprite("UI/world.png");
	time_image = new Sprite("UI/time.png");
}

/**
 * @brief 更新処理
 * @param[in] delta_second 前フレームからの経過時間（秒）
 * @return eSceneType 遷移先のシーンタイプ
 */
eSceneType ResultScene::Update(float delta_second)
{


	// 決定操作（キーボードのSPACE、またはコントローラーのSTARTボタン）を検知
	if (InputManager::GetKeyState(KEY_INPUT_SPACE) == eInputState::ePressed ||
		InputManager::GetButtonState(XINPUT_BUTTON_START) == eInputState::ePressed)
	{
		// タイトル画面へ遷移
		return eSceneType::eTitle;
	}

	// イベントがなければ現在のシーン（リザルト）を維持
	return GetNowSceneType();
}

/**
 * @brief 描画処理
 * @details 背景画像と、点滅するゲームオーバーテキストを画面に描画します。
 */
void ResultScene::Draw() const
{
	DrawBox(0, 0, 1024, 768, GetColor(0, 0, 0), TRUE);
	DrawRotaGraph(412, 384, 2, 0.0, (*mario_image)[0], TRUE);
	DrawRotaGraph(512, 384, 2, 0.0, (*mario_stock)[11], TRUE);
	DrawRotaGraph(612, 390, 2, 0.0, (*mario_stock)[stock], TRUE);
	DrawRotaGraph(162, 40, 2, 0.0, (*mario_name)[0], TRUE);
	DrawRotaGraph(662, 40, 2, 0, world_image->GetHandle(), TRUE);
	DrawRotaGraph(412, 304, 2, 0, world_image->GetHandle(), TRUE);
	DrawRotaGraph(530, 304, 2, 0.0, (*mario_stock)[1], TRUE);
	DrawRotaGraph(570, 304, 2, 0.0, (*mario_stock)[10], TRUE);
	DrawRotaGraph(610, 304, 2, 0.0, (*mario_stock)[1], TRUE);
	DrawRotaGraph(622, 80, 2, 0.0, (*mario_stock)[1], TRUE);
	DrawRotaGraph(662, 80, 2, 0.0, (*mario_stock)[10], TRUE);
	DrawRotaGraph(702, 80, 2, 0.0, (*mario_stock)[1], TRUE);
	DrawRotaGraph(862, 40, 2, 0, time_image->GetHandle(), TRUE);
	DrawRotaGraph(362, 80, 2, 0.0, (*coin_image)[0], TRUE);
	DrawRotaGraph(392, 80, 2, 0.0, (*mario_stock)[11], TRUE);
	DrawRotaGraph(422, 80, 2, 0.0, (*mario_stock)[(coin_count / 10) % 10], TRUE); // 十の位
	DrawRotaGraph(452, 80, 2, 0.0, (*mario_stock)[(coin_count / 1) % 10], TRUE); // 一の位
	DrawRotaGraph(98, 80, 2, 0.0, (*mario_stock)[(score / 100000) % 10], TRUE); // 十万の位
	DrawRotaGraph(128, 80, 2, 0.0, (*mario_stock)[(score / 10000) % 10], TRUE); // 万の位
	DrawRotaGraph(158, 80, 2, 0.0, (*mario_stock)[(score / 1000) % 10], TRUE); // 千の位
	DrawRotaGraph(188, 80, 2, 0.0, (*mario_stock)[(score / 100) % 10], TRUE); // 百の位
	DrawRotaGraph(218, 80, 2, 0.0, (*mario_stock)[(score / 10) % 10], TRUE); // 十の位
	DrawRotaGraph(248, 80, 2, 0.0, (*mario_stock)[(score / 1) % 10], TRUE); // 一の位
}

/**
 * @brief 終了（解放）処理
 */
void ResultScene::Finalize()
{
	// 必要に応じてDeleteFontToHandleなどの解放処理をここに記述
}

/**
 * @brief 自身のシーンタイプを取得
 * @return eSceneType::eResult
 */
eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}
