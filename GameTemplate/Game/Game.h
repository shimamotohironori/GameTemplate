#pragma once
#include "sound/SoundSource.h"
#include "Level3DRender/LevelRender.h"

class Player;
class Enemy;
class BackGround;
class GameCamera;
class DeathBall;
class Lever;
class Door;
class GameClear;
class Goal;
class Toge;
class Trap;
class Kabe;
class DeathCounter;
//class MovingFloor;
class Map;

class Game : public IGameObject
{
public:
	Game() {}
	~Game();
	void BALL();
	void ENEMY();
	void TOGE();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	bool			m_isHit = false;
private:
	ModelRender m_modelRender;
	ModelRender m_background;
	SpriteRender m_spriteRender;         //スプライトレンダー。
	FontRender m_fontRender;
	FontRender m_fontRender2;
	LevelRender	m_levelRender;				//レベル。
	BackGround* m_backGround=nullptr;       //背景
	Player* player = nullptr;                         //プレイヤー
	Player* m_player;
	Enemy* enemy = nullptr;                           //エネミー
	GameCamera* gameCamera = nullptr;                 //ゲームカメラ
	GameCamera* m_gameCamera;
	DeathBall* deathBall;                   //デスボール
	GameClear* gameClear;                   //ゲームクリア
	SoundSource* gameBGM;		            //ゲーム中のBGM。
	Goal* goal;                             //ゴール
	Toge* toge;                             //棘
	Door* door;                             //ドア
	Lever* lever;                           //レバー
	Trap* trap;                             //トラップ
	Kabe* kabe;                             //壁
	DeathCounter* deathCounter;             
	//MovingFloor* m_movingFloor = nullptr;
	Map* m_map = nullptr;                   //マップ
	std::vector<Lever*>	m_leverVector;		//レバーの配列。
	std::vector<Door*>	m_doorVector;		//ドアの配列。
	float m_timer = 0.0f;
	float m_timer2 = 0.0f;
	float m_timer3 = 0.0f;
	float m_get = 0.0f;
};

