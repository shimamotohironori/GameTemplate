#include "stdafx.h"
#include "Title.h"
#include "Game.h"
//#include "Description.h"
#include "sound/SoundEngine.h"


bool Title::Start()
{
	//タイトル。
	spriteRender.Init("Assets/sprite/Title.dds", 1920.0f, 1080.0f);
	//spriteRender.Init("Assets/sprite/Result.dds", 1920.0f, 1280.0f);
	//タイトルのBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/titlebgm.wav");
	//g_soundEngine->ResistWaveFileBank(0, "Assets/sound/GameOver.wav");
	//タイトルのBGMを再生する。
	titleBGM = NewGO<SoundSource>(0);
	titleBGM->Init(0);
	titleBGM->Play(true);
	titleBGM->SetVolume(0.2f);

	//効果音(ボイス)
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/Yukkuri.wav");

	return true;
}

Title::~Title()
{
	//タイトルのBGMを削除する。
	DeleteGO(titleBGM);
}

void Title::Update()
{
	spriteRender.Update();
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0, "game");
		DeleteGO(this);

		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(5);
		se->Play(false);
		se->SetVolume(1.0f);
	}
}

void Title::Render(RenderContext& rc)
{
	//画像を描画する。
	spriteRender.Draw(rc);
}