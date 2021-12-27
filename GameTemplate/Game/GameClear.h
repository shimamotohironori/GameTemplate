#pragma once
#include "sound/SoundSource.h"

class GameClear :public IGameObject
{
public:
	GameClear() {};
	~GameClear();
	bool Start();
	//描画処理。
	void Render(RenderContext& rc);
	//更新処理。
	void Update();
	//スプライトレンダー。
	SpriteRender spriteRender;
	//Description* description;  //ゲーム説明。 
	SoundSource* gameClearBGM;			//タイトルのBGM。
};

