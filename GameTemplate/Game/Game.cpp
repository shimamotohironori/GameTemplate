#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Title.h"
#include "Player.h"
#include "Enemy.h"
#include "GameCamera.h"
#include"DeathBall.h"
#include "GameOver.h"
#include "Lever.h"
#include "Door.h"
#include "GameClear.h"
#include "sound/SoundEngine.h"
#include "Goal.h"
#include "Toge.h"
#include "Trap.h"
#include "Kabe.h"
#include "DeathCounter.h"
#include "Map.h"
#include "MovingFloor.h"

namespace
{
	Vector3 BACKGROUND_SCALE = Vector3(0.7f, 1.0f, 0.7f);
}

void Game::BALL()
{
	//デスボール
	deathBall = NewGO<DeathBall>(0, "deathBall");
	deathBall->position = { -2000.0f,1000.0f,12.0f };
	deathBall->Position = deathBall->position;

/*	DeathBall* deathBall2 = NewGO<DeathBall>(0, "deathBall");
	deathBall2->position = { -4000.0f,1500.0f,40.0f };
	deathBall2->Position = deathBall2->position;

	DeathBall* deathBall3 = NewGO<DeathBall>(0, "deathBall");
	deathBall3->position = { -6000.0f,2600.0f,60.0f };
	deathBall3->Position = deathBall3->position;

	DeathBall* deathBall4 = NewGO<DeathBall>(0, "deathBall");
	deathBall4->position = { -8000.0f,2600.0f,60.0f };
	deathBall4->Position = deathBall3->position;

	DeathBall* deathBall5 = NewGO<DeathBall>(0, "deathBall");
	deathBall5->position = { -10000.0f,2600.0f,60.0f };
	deathBall5->Position = deathBall3->position;

	DeathBall* deathBall6 = NewGO<DeathBall>(0, "deathBall");
	deathBall6->position = { -7450.0f,2600.0f,7.0f };
	deathBall6->Position = deathBall3->position;
	/*
	DeathBall* deathBall7 = NewGO<DeathBall>(0, "deathBall");
	deathBall7->position = { -10000.0f,2600.0f,60.0f };
	deathBall7->Position = deathBall3->position;*/
}

Game::~Game()
{
	//トラップの削除。
	//DeleteGO(trap);

	//エネミーの削除。
	DeleteGO(enemy);
	//ゲームカメラの削除。
	DeleteGO(gameCamera);
	//背景の削除。
	const auto& backGrounds = FindGOs<BackGround>("backGround");
	for (auto& backGround : backGrounds)
	{
		DeleteGO(m_backGround);
	}

	//ゲームBGMの削除。
	DeleteGO(gameBGM);
	//ゴールの削除。
	DeleteGO(goal);
	//壁の削除。
	DeleteGO(kabe);
	//ドアの削除。
	DeleteGO(door);
	//レバーの削除。
	DeleteGO(lever);

	//棘の削除。
	const auto& toges = FindGOs<Toge>("toge");
	for (auto toge : toges)
	{
		DeleteGO(toge);
	}


	//DeleteGO(deathBall);
	const auto& deathBalls = FindGOs<DeathBall>("deathBall");
	for (auto deathBall : deathBalls)
	{
		//デスボールを削除する。
		DeleteGO(deathBall);
	}

	//プレイヤーの削除。
	DeleteGO(player);

}

bool Game::Start()
{
	//プレイヤーの生成。
	player = NewGO<Player>(0,"player");
	//エネミーの生成。
	enemy = NewGO<Enemy>(0, "enemy");
	enemy->m_position = { 20000.0f, 30.0f, 30.0f };//エネミーの座標。
	//ゲームカメラの生成。
	gameCamera = NewGO<GameCamera>(0, "gameCamera");

	BALL();


 //レベルを構築する。
	
	m_levelRender.Init("Assets/levelData/BackGround5.tkl",
		[&](LevelObjectData& objData)
		{
			//名前がbackGroundだったら。
			if (objData.EqualObjectName(L"stage3") == true) {
				//背景オブジェクトを作成する。
				m_backGround = NewGO<BackGround>(0, "backGround");
				//座標を設定する。
				m_backGround->SetPosition(objData.position);
				//大きさを設定する。
				m_backGround->SetScale(objData.scale);
				//回転を設定する。
				m_backGround->SetRotation(objData.rotation);
				return true;
			}
			
			//名前がGoalだったら
			else if (objData.EqualObjectName(L"Goal") == true) {
				//背景オブジェクトを作成する。
				auto goal = NewGO<Goal>(0, "goal");
				//座標を設定する。
				goal->SetPosition(objData.position);
				//大きさを設定する。
				goal->SetScale(objData.scale);
				//回転を設定する。
				goal->SetRotation(objData.rotation);
				return true;
			}
			
			//名前がkabeだったら
			else if (objData.EqualObjectName(L"kabe") == true) {
				//背景オブジェクトを作成する。
				auto kabe = NewGO<Kabe>(0, "kabe");
				//座標を設定する。
				kabe->SetPosition(objData.position);
				//大きさを設定する。
				kabe->SetScale(objData.scale);
				//回転を設定する。
				kabe->SetRotation(objData.rotation);
				return true;
			}
			//名前がTrapだったら
			/*else if (objData.EqualObjectName(L"Trap") == true) {
				//背景オブジェクトを作成する。
				auto trap = NewGO<Trap>(0, "trap");
				//座標を設定する。
				trap->SetPosition(objData.position);
				//大きさを設定する。
				trap->SetScale(objData.scale);
				//回転を設定する。
				//goal->SetRotation(objData.rotation);
				return true;
			}*/

			//名前がtogeだったら
			else if (objData.ForwardMatchName(L"toge") == true) {
				//背景オブジェクトを作成する。
				auto toge = NewGO<Toge>(0, "toge");
				//座標を設定する。
				toge->SetPosition(objData.position);
				//大きさを設定する。
				toge->SetScale(objData.scale);
				//回転を設定する。
				toge->SetRotation(objData.rotation);
				//番号を設定する。
				toge->SetTogeNumber(objData.number);
				return true;
			}

			//名前がleverだったら。
			else if (objData.ForwardMatchName(L"lever") == true)
			{
				//レバーのオブジェクトを作成する。
				auto lever = NewGO<Lever>(0, "lever");
				//座標を設定する。
				lever->SetPosition(objData.position);
				//大きさを設定する。
				lever->SetScale(objData.scale);
				//回転を設定する。
				lever->SetRotation(objData.rotation);
				//レバーの配置に作成したオブジェクトを加える。
				m_leverVector.push_back(lever);
				//番号を設定する。
				lever->SetLeverNumber(objData.number);
				return true;
			}

			//名前がdoorだったら。
			else if (objData.ForwardMatchName(L"door") == true)
			{
				//ドアのオブジェクトを作成する。
				auto door = NewGO<Door>(0, "door");
				//座標を設定する。
				door->SetPosition(objData.position);
				//大きさを設定する。
				door->SetScale(objData.scale);
				//回転を設定する。
				door->SetRotation(objData.rotation);
				//番号を設定する。
				door->SetDoorNumber(objData.number);
				//ドアの配置に作成したオブジェクトを加える。
				m_doorVector.push_back(door);
				
				return true;
			}

			return true;
		});

		//マップの作成
		//m_map = NewGO<Map>(0, "Map");
		

	//当たり判定有効化
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	SkyCube* m_skycube = NewGO<SkyCube>(0,"skycube");
	//m_skycube.SetScale({ 8.0f,8.0f, 12.0f });

	//ゲーム中のBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/gamebgm3.wav");
	//ゲーム中のBGMを再生する。
	gameBGM = NewGO<SoundSource>(0);
	gameBGM->Init(2);
	gameBGM->Play(true);
	gameBGM->SetVolume(0.2f);



	m_spriteRender.Init("Assets/sprite/MAP.dds", 512.0f, 720.0f);
	m_spriteRender.Update();

	return true;
}

void Game::Update()
{
	//マップ←仮置き
	m_spriteRender.SetPosition({ 670.0f,200.0f,0.0f });
	m_spriteRender.Update();
	//時間
	m_timer += g_gameTime->GetFrameDeltaTime();
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%d秒経過!!", int(m_timer));

	//表示するテキストを設定。
	m_fontRender2.SetText(wcsbuf);
	//フォントの位置を設定。
	m_fontRender2.SetPosition(Vector3(-200.0f, 500.0f, 2000.0f));
	//フォントの大きさを設定。
	m_fontRender2.SetScale(2.0f);
	//フォントの色を設定。
	m_fontRender2.SetColor(g_vec4Black);

	
	//m_modelRender.Update();

	m_timer2 += g_gameTime->GetFrameDeltaTime();
	//100秒たったらゲームオーバー
	if (m_timer2 >= 100.0f)
	{
		NewGO<GameOver>(0, "gameOver");
		DeleteGO(this);
	}
	

	
	//いろいろ当たったらゲームオーバー。
	if (player->deathBallCount == 1||
		player->togeCount == 1||
		player->enemyCount == 1)
	{
		NewGO<GameOver>(0, "gameOver");
		DeleteGO(this);
	}
	if (player->goalCount == 1)//ゴールにあたったらゲームクリア。
	{
		NewGO<GameClear>(0, "gameClear");
		DeleteGO(this);
	}
	
	//プレイヤーのyの座標が-500以下になったらげーむおーばー
	if (FindGO<Player>("player")->position.y <= -500.0f)
	{
		NewGO<GameOver>(0, "gameOver");
		DeleteGO(this);
	}

}

void Game::Render(RenderContext& rc)
{
	//m_modelRender.Draw(rc);
	m_spriteRender.Draw(rc);
	//m_fontRender.Draw(rc);
	m_fontRender2.Draw(rc);
}