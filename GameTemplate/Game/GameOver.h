#pragma once
#include "sound/SoundSource.h"
class Player;
class Enemy;
class GameOver :public IGameObject
{
public:
	GameOver();
	~GameOver();
	//�`�揈���B
	void Render(RenderContext& rc);
	//�X�V�����B
	void Update();
	//�X�v���C�g�����_�[�B
	SpriteRender spriteRender;
	SoundSource* gameoverbgm;			//�^�C�g����BGM�B
	Player* player;
	Enemy* enemy;
};



