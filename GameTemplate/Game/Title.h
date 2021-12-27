#pragma once
#include "sound/SoundSource.h"

class Title :public IGameObject
{
public:
	Title() {};
	~Title();
	bool Start();
	//�`�揈���B
	void Render(RenderContext& rc);
	//�X�V�����B
	void Update();
	//�X�v���C�g�����_�[�B
	SpriteRender spriteRender;
	//Description* description;  //�Q�[�������B 
	SoundSource* titleBGM;			//�^�C�g����BGM�B
};

