#include"InGameScene.h"
#include"../File/AssetContainer.h"
#include"../File/StageData.h"
#include"../Input/InputManager.h"

#include"../Actor/Character/Mario.h"
#include"../Actor/Character/Enemy/kuribo-.h"
#include"../Actor/Character/Enemy/nokonoko.h"
#include"../Actor/Item/OneUpMushroom.h"
#include"../Actor/Item/FireFlower.h"
#include"../Actor/Item/Mushroom.h"
#include"../Actor/Item/SuperStar.h"

#include <DxLib.h>
#include <fstream>
#include <sstream>

InGameScene::InGameScene()
    :SceneBase()
    ,player(nullptr)
    ,enemy(nullptr)
    ,font_handle(NULL)
    , camera_x(0.0f)
    , floor(-1)
    , hatena(nullptr)
    , block(-1)
    , hard_block(-1)
    , dokan_lu(-1)
    , dokan_ru(-1)
    , dokan_ld(-1)
    , dokan_rd(-1)
    , pole(-1)
    , pole_top(-1)
    , flag(-1)
    , fort(-1)
    , cloud0(-1),cloud1(-1),cloud2(-1),cloud3(-1),cloud4(-1),cloud5(-1)
    , ha0(-1),ha1(-1),ha2(-1)
    , Mt0(-1),Mt1(-1),Mt2(-1),Mt3(-1),Mt4(-1),Mt5(-1)
    , sky(-1)
{

}

InGameScene::~InGameScene()
{
    Finalize();
}

void InGameScene::Initialize()
{
    //画像アセット読み込み
    floor = AssetContainer::Get()->GetImages("Block/floor.png");
    block = AssetContainer::Get()->GetImages("Block/block.png");
    hard_block = AssetContainer::Get()->GetImages("Block/kai_block.png");

    dokan_lu = AssetContainer::Get()->GetImages("dokan_left_up.png");
    dokan_ru = AssetContainer::Get()->GetImages("dokan_right_up.png");
    dokan_ld = AssetContainer::Get()->GetImages("dokan_left_down.png");
    dokan_rd = AssetContainer::Get()->GetImages("dokan_right_down.png");

    pole = AssetContainer::Get()->GetImages("pole_down.png");
    pole_top = AssetContainer::Get()->GetImages("pole.png");
    flag = AssetContainer::Get()->GetImages("flag.png");
    fort = AssetContainer::Get()->GetImages("siro1.png");

    hatena = new DivSprite("Block/hatena.png", 4, 1);

    cloud0= AssetContainer::Get()->GetImages("cloud1.png");
    cloud1= AssetContainer::Get()->GetImages("cloud2.png");
    cloud2= AssetContainer::Get()->GetImages("cloud3.png");
    cloud3= AssetContainer::Get()->GetImages("cloud4.png");
    cloud4= AssetContainer::Get()->GetImages("cloud5.png");
    cloud5= AssetContainer::Get()->GetImages("cloud6.png");

    ha0= AssetContainer::Get()->GetImages("ha0.png");
    ha1= AssetContainer::Get()->GetImages("ha1.png");
    ha2= AssetContainer::Get()->GetImages("ha2.png");

    Mt0= AssetContainer::Get()->GetImages("mountain_left.png");
    Mt1= AssetContainer::Get()->GetImages("mountain_right.png");
    Mt2= AssetContainer::Get()->GetImages("mountain_surface.png");
    Mt3= AssetContainer::Get()->GetImages("mountain_surface1.png");
    Mt4= AssetContainer::Get()->GetImages("mountain_surface2.png");
    Mt5= AssetContainer::Get()->GetImages("mountain_up.png");

    sky= AssetContainer::Get()->GetImages("sora.png");

    //ステージデータの初期化とCSV読み込み
    StageData::Get();
    LoadBackgroundData();
    LoadStageData();

	player = new Mario();
	player->Initialize();
    owned_actors.push_back(player);
}

eSceneType InGameScene::Update(float delta_second)
{
    PlayUpdate(delta_second);
    return eSceneType::eInGame;
}

void InGameScene::Draw() const
{
    const float draw_chip_size = 768.0f / 14.0f;
    //全体を空画像で埋めつくす
    if (sky != -1)
    {
        for (int y = 0;y<14;++y)
        {
            for (int x = 0;x<=static_cast<int>(1024.0f/draw_chip_size)+1;++x)
            {
                int x1 = static_cast<int>(x * draw_chip_size);
                int y1 = static_cast<int>(y * draw_chip_size);
                int x2 = static_cast<int>((x + 1) * draw_chip_size);
                int y2 = static_cast<int>((y + 1) * draw_chip_size);
                DrawExtendGraph(x1,y1,x2,y2, sky, TRUE);
            }
        }
    }
    
    //先に背景を描画する
    for (size_t y = 0; y < bg_data.size(); ++y)
    {
        for (size_t x = 0; x < bg_data[y].size();++x)
        {
            const std::string& cell = bg_data[y][x];
            if (cell == "0" || cell.empty())
            {
                continue;
            }

            //背景描画の座標設定（camera_x を引く）
            int x1 = static_cast<int>(x * draw_chip_size - camera_x);
            int y1 = static_cast<int>(y * draw_chip_size);
            int x2 = static_cast<int>((x + 1) * draw_chip_size - camera_x);
            int y2 = static_cast<int>((y + 1) * draw_chip_size);

            // 画面外のタイルは描画をスキップ（処理負荷の軽減）
            if (x2 < 0 || x1 > 1024) continue;

            int handle = -1;

            if (cell == "z")
            {
                handle = cloud0;
            }
            else if (cell == "h")
            {
                handle = cloud1;
            }
            else if (cell == "i")
            {
                handle = cloud2;
            }
            else if (cell == "j")
            {
                handle = cloud3;
            }
            else if (cell == "k")
            {
                handle = cloud4;
            }
            else if (cell == "l")
            {
                handle = cloud5;
            }
            else if (cell == "x")
            {
                handle = ha1;
            }
            else if (cell == "a")
            {
                handle = ha0;
            }
            else if (cell == "b")
            {
                handle = ha2;
            }
            else if (cell == "y")
            {
                handle = Mt2;
            }
            else if (cell == "c")
            {
                handle = Mt0;
            }
            else if (cell == "d")
            {
                handle = Mt1;
            }
            else if (cell == "e")
            {
                handle = Mt5;
            }
            else if (cell == "f")
            {
                handle = Mt3;
            }
            else if (cell == "g")
            {
                handle = Mt4;
            }
           

            if (handle != -1)
            {
                DrawExtendGraph(x1, y1, x2, y2, handle, TRUE);
            }
        }
    }
    //ステージを描画する
    const auto& stage_map = StageData::Get()->GetAll();
    for (size_t y = 0;y < stage_map.size();++y)
    {
        for (size_t x = 0;x < stage_map[y].size();++x)
        {
            ePanelID id = stage_map[y][x];
            if (id == ePanelID::eNone||id==ePanelID::eFlag)
            {
                continue;
            }

            //ステージ描画の座標設定（camera_x を引く）
            int x1 = static_cast<int>(x * draw_chip_size - camera_x);
            int y1 = static_cast<int>(y * draw_chip_size);
            int x2 = static_cast<int>((x + 1) * draw_chip_size - camera_x);
            int y2 = static_cast<int>((y + 1) * draw_chip_size);

            //城画像の場合は5*5マス分のサイズに描画領域を広げる
            if (id == ePanelID::eFort)
            {
                int fort_scale = static_cast<int>(StageData::FORT_CHIP_SIZE / StageData::CHIP_SIZE);
                x2 = static_cast<int>((x + fort_scale) * draw_chip_size - camera_x);
                y2 = static_cast<int>((y + fort_scale) * draw_chip_size);
            }
            

            // 画面外のタイルは描画をスキップ
            if (x2 < 0 || x1 > 1024) continue;


            int Stage_handle = -1;

            switch (id)
            {
            case ePanelID::eWall:
                Stage_handle = floor;
                break;

            case ePanelID::eBlock:
                Stage_handle = block;
                break;
            
            case ePanelID::eHatena:
                Stage_handle = (*hatena)[0];
                break;

            case ePanelID::eHardBlock:
                Stage_handle = hard_block;
                break;

            case ePanelID::eDokan_a:
                Stage_handle = dokan_lu;
                break;

            case ePanelID::eDokan_b:
                Stage_handle = dokan_ru;
                break;

            case ePanelID::eDokan_c:
                Stage_handle = dokan_ld;
                break;

            case ePanelID::eDokan_d:
                Stage_handle = dokan_rd;
                break;

            case ePanelID::ePole:
                Stage_handle = pole;
                break;

            case ePanelID::eFort:
                Stage_handle = fort;
                break;

            case ePanelID::ePoleTop:
                Stage_handle = pole_top;
                break;

            default:
                Stage_handle = floor;
                break;
            }

            if (Stage_handle != -1)
            {
                DrawExtendGraph(x1, y1, x2, y2, Stage_handle, TRUE);
            }
            
        }
    }

    for (size_t y = 0;y < stage_map.size();++y)
    {
        for (size_t x = 0;x < stage_map[y].size();++x)
        {
            if (stage_map[y][x] == ePanelID::eFlag && flag != -1)
            {
                int half_chip = static_cast<int>(draw_chip_size * 0.5f);
                int x1 = static_cast<int>(x * draw_chip_size - camera_x) + half_chip;
                int y1 = static_cast<int>(y * draw_chip_size);
                int x2 = static_cast<int>((x + 1) * draw_chip_size - camera_x) + half_chip;
                int y2 = static_cast<int>((y + 1) * draw_chip_size);

                if (x2 < 0 || x1>1024)
                {
                    continue;
                }

                DrawExtendGraph(x1, y1, x2, y2, flag, TRUE);
            }
        }
    }

    //キャラクターの描画（camera_x を渡す）
    for (Actor* actor : owned_actors)
    {
        if (actor)
        {
            actor->Draw(camera_x);
        }
    }
}

void InGameScene::Finalize()
{
    //アクタを解放する
    for (auto actor : owned_actors)
    {
        delete actor;
    }
    owned_actors.clear();

    if (hatena)
    {
        delete hatena;
        hatena = nullptr;
    }
}

eSceneType InGameScene::GetNowSceneType() const
{
    return eSceneType::eInGame;
}

void InGameScene::LoadStageData()
{
    //ステージの読み込み
    std::string stage1 = "assets/data/mario_stage_2d_array.csv";
    std::string stage2 = "assets/data/mario_underground_2d_array.csv";
    std::ifstream file(stage1);
    //何もなかったらやり直し
    if (!file.is_open())
    {
        return;
    }

    //CSVの行を1行ずつ読み込む
    std::string line;
    int y = 0;

    while (std::getline(file, line))
    {
        //空行はスキップ
        if (line.empty())
        {
            continue;
        }
        //CSVの行をカンマ分割で処理
        std::stringstream ss(line);
        std::string cell;
        int x = 0;

        //CSVのセルを1つずつ処理
        while (std::getline(ss, cell, ','))
        {
            if (!cell.empty())
            {
                //ステージデータの座標計算
                Vector2 pos(
                    StageData::STAGE_OFFSET_X + x * StageData::CHIP_SIZE,
                    StageData::STAGE_OFFSET_Y + y * StageData::CHIP_SIZE
                    //x*StageData::CHIP_SIZE,
                    //y*StageData::CHIP_SIZE
                );

                if (cell == "1")
                {
                    StageData::Get()->SetPanelData(ePanelID::eWall, pos, 1, 1);
                }
                else if (cell == "2")
                {
                    StageData::Get()->SetPanelData(ePanelID::eHatena, pos, 1, 1);
                }
                else if (cell == "3")
                {
                    StageData::Get()->SetPanelData(ePanelID::eBlock, pos, 1, 1);
                }
                else if (cell == "4")
                {
                    StageData::Get()->SetPanelData(ePanelID::eHardBlock, pos, 1, 1);
                }
                else if (cell == "5")
                {
                    Kuribo* new_enemy=new Kuribo(pos);
                    owned_actors.push_back(new_enemy);
                }
                else if (cell == "6")
                {
                    Nokonoko* new_enemy= new Nokonoko(pos);
                    owned_actors.push_back(new_enemy);
                }

                else if (cell == "a")
                {
                    StageData::Get()->SetPanelData(ePanelID::eDokan_a, pos, 1, 1);
                }
                else if (cell == "b")
                {
                    StageData::Get()->SetPanelData(ePanelID::eDokan_b, pos, 1, 1);
                }
                else if (cell == "c")
                {
                    StageData::Get()->SetPanelData(ePanelID::eDokan_c, pos, 1, 1);
                }
                else if (cell == "d")
                {
                    StageData::Get()->SetPanelData(ePanelID::eDokan_d, pos, 1, 1);
                }
                else if (cell == "7")
                {
                    StageData::Get()->SetPanelData(ePanelID::ePole, pos, 1, 1);
                }
                else if (cell == "8")
                {
                    StageData::Get()->SetPanelData(ePanelID::ePoleTop, pos, 1, 1);
                }
                else if (cell == "f")
                {
                    StageData::Get()->SetPanelData(ePanelID::eFlag, pos, 1, 1);
                }
                else if (cell == "g")
                {
                    StageData::Get()->SetPanelData(ePanelID::eFort, pos, 1, 1);
                }
            }
            x++;
        }
        y++;
    }

}

void InGameScene::LoadBackgroundData()
{
    std::string back_stage = "assets/data/mario_clouds_hills_bushes_only.csv";
    std::ifstream file(back_stage);
    //開けなかったらやり直し
    if (!file.is_open())
    {
        OutputDebugStringA("CSVファイルの読み込みに失敗しました");
        return;
    }
    bg_data.clear();
    std::string line;

    while (std::getline(file, line))
    {
        //空行はスキップ
        if (line.empty())
        {
            continue;
        }
        //CSVの行をカンマ分割で処理
        std::stringstream ss(line);
        //CSVのセルを1つずつ処理
        std::string cell;
        //CSVの行を格納するベクター
        std::vector<std::string> row;

        //SCVのセルを１つずつ処理
        while (std::getline(ss, cell, ','))
        {
            //空セルはスキップ
            row.push_back(cell);
        }
        bg_data.push_back(row);
    }
}

void InGameScene::ChangeGameState(eGameState new_state)
{
    state = new_state;
}

void InGameScene::PlayUpdate(float delta_second)
{
    //アクタの更新
    for (auto actor : owned_actors)
    {
        if (actor)
        {
            actor->Update(delta_second);
        }
    }

    // カメラ追従処理
    if (player != nullptr)
    {
        const float screen_width = 1024.0f;
        const float center_x = screen_width * 0.5f;

        // マリオが画面中央より右に進んだらカメラを進める（左スクロールはしない本編仕様）
        if (player->GetLocation().x - camera_x > center_x)
        {
            camera_x = player->GetLocation().x - center_x;
        }

        // ステージ右端のスクロール上限（stage_mapの横幅分まで）
        const float draw_chip_size = 768.0f / 14.0f;
        const auto& stage_map = StageData::Get()->GetAll();
        if (!stage_map.empty() && !stage_map[0].empty())
        {
            float max_camera_x = (stage_map[0].size() * draw_chip_size) - screen_width;
            if (max_camera_x < 0.0f) max_camera_x = 0.0f;
            if (camera_x > max_camera_x) camera_x = max_camera_x;
        }

        // マリオがカメラの左端より後ろに戻れないように制限
        if (player->GetLocation().x < camera_x + 16.0f)
        {
            Vector2 pos = player->GetLocation();
            pos.x = camera_x + 16.0f;
            player->SetLocation(pos);
        }
    }
}
void InGameScene::CheckCollision()
{

}