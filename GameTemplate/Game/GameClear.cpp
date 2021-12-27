#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundEngine.h"

bool GameClear::Start()
{
	//�Q�[���N���A�B
	spriteRender.Init("Assets/sprite/GameClear2.dds", 1920.0f, 1080.0f);
	//spriteRender.Init("Assets/sprite/Result.dds", 1920.0f, 1280.0f);
	//�Q�[���N���A��BGM��ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/GameClear.wav");
	//�Q�[���N���A��BGM���Đ�����B
	gameClearBGM = NewGO<SoundSource>(0);
	gameClearBGM->Init(4);
	gameClearBGM->Play(true);
	gameClearBGM->SetVolume(0.2f);


	//���ʉ�(�{�C�X)
	g_soundEngine->ResistWaveFileBank(9, "Assets/sound/TitleBack.wav");
	return true;
}

GameClear::~GameClear()
{
	//�Q�[���N���A��BGM���폜����B
	DeleteGO(gameClearBGM);
}

void GameClear::Update()
{
	//A�{�^���������ꂽ��^�C�g���Ɉړ�
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
	//�摜��`�悷��B
	spriteRender.Draw(rc);
}