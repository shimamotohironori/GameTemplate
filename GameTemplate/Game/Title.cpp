#include "stdafx.h"
#include "Title.h"
#include "Game.h"
//#include "Description.h"
#include "sound/SoundEngine.h"


bool Title::Start()
{
	//�^�C�g���B
	spriteRender.Init("Assets/sprite/Title.dds", 1920.0f, 1080.0f);
	//spriteRender.Init("Assets/sprite/Result.dds", 1920.0f, 1280.0f);
	//�^�C�g����BGM��ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/titlebgm.wav");
	//g_soundEngine->ResistWaveFileBank(0, "Assets/sound/GameOver.wav");
	//�^�C�g����BGM���Đ�����B
	titleBGM = NewGO<SoundSource>(0);
	titleBGM->Init(0);
	titleBGM->Play(true);
	titleBGM->SetVolume(0.2f);

	//���ʉ�(�{�C�X)
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/Yukkuri.wav");

	return true;
}

Title::~Title()
{
	//�^�C�g����BGM���폜����B
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
	//�摜��`�悷��B
	spriteRender.Draw(rc);
}