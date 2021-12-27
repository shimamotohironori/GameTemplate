#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundEngine.h"

bool GameClear::Start()
{
	//ゲームクリア。
	spriteRender.Init("Assets/sprite/GameClear2.dds", 1920.0f, 1080.0f);
	//spriteRender.Init("Assets/sprite/Result.dds", 1920.0f, 1280.0f);
	//ゲームクリアのBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/GameClear.wav");
	//ゲームクリアのBGMを再生する。
	gameClearBGM = NewGO<SoundSource>(0);
	gameClearBGM->Init(4);
	gameClearBGM->Play(true);
	gameClearBGM->SetVolume(0.2f);


	//効果音(ボイス)
	g_soundEngine->ResistWaveFileBank(9, "Assets/sound/TitleBack.wav");
	return true;
}

GameClear::~GameClear()
{
	//ゲームクリアのBGMを削除する。
	DeleteGO(gameClearBGM);
}

void GameClear::Update()
{
	//Aボタンが押されたらタイトルに移動
	spriteRender.Update();
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Title>(0, "tilte");
		DeleteGO(this);
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(9);
		se->Play(false);
		se->SetVolume(1.0f);
	}
}

void GameClear::Render(RenderContext& rc)
{
	//画像を描画する。
	spriteRender.Draw(rc);
}