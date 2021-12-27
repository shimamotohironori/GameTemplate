#include "stdafx.h"
#include "GameOver.h"
#include "Game.h"
#include "Title.h"
#include "sound/SoundEngine.h"
#include"Player.h"
#include"Enemy.h"

GameOver::GameOver()
{
	//ゲームオーバー。
	spriteRender.Init("Assets/sprite/YouAreDead2.dds", 1920.0f, 1080.0f);
	//ゲームオーバーのBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/gameoverbgm.wav");
	//ゲームオーバーのBGMを再生する。
	gameoverbgm = NewGO<SoundSource>(0);
	gameoverbgm->Init(3);
	gameoverbgm->Play(true);
	gameoverbgm->SetVolume(0.2f);
	//player = FindGO<Player>("player");

	//効果音(ボイス)
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/ReStart.wav");
	//効果音(ボイス)
	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/TitleBack.wav");
	
}

GameOver::~GameOver()
{
	//タイトルのBGMを削除する。
	DeleteGO(gameoverbgm);
	//プレイヤーの削除。
	//DeleteGO(player);
	//エネミーの削除。
	//DeleteGO(enemy);
}

void GameOver::Update()
{
	spriteRender.Update();
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		NewGO<Title>(0, "title");
		DeleteGO(this);
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(8);
		se->Play(false);
		se->SetVolume(1.0f);
	}
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0, "game");
		DeleteGO(this);
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(7);
		se->Play(false);
		se->SetVolume(1.0f);
	}
}

void GameOver::Render(RenderContext& rc)
{
	//画像を描画する。
	spriteRender.Draw(rc);
}
