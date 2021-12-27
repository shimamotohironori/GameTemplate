#pragma once
#include "sound/SoundSource.h"

class GameClear :public IGameObject
{
public:
	GameClear() {};
	~GameClear();
	bool Start();
	//�`�揈���B
	void Render(RenderContext& rc);
	//�X�V�����B
	void Update();
	//�X�v���C�g�����_�[�B
	SpriteRender spriteRender;
	//Description* description;  //�Q�[�������B 
	SoundSource* gameClearBGM;			//�^�C�g����BGM�B
};

