#pragma once
#include "sound/SoundSource.h"
class Player;
class Enemy;
class GameOver :public IGameObject
{
public:
	GameOver();
	~GameOver();
	//描画処理。
	void Render(RenderContext& rc);
	//更新処理。
	void Update();
	//スプライトレンダー。
	SpriteRender spriteRender;
	SoundSource* gameoverbgm;			//タイトルのBGM。
	Player* player;
	Enemy* enemy;
};



