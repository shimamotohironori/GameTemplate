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
	SpriteRender m_spriteRender;         //�X�v���C�g�����_�[�B
	FontRender m_fontRender;
	FontRender m_fontRender2;
	LevelRender	m_levelRender;				//���x���B
	BackGround* m_backGround=nullptr;       //�w�i
	Player* player = nullptr;                         //�v���C���[
	Player* m_player;
	Enemy* enemy = nullptr;                           //�G�l�~�[
	GameCamera* gameCamera = nullptr;                 //�Q�[���J����
	GameCamera* m_gameCamera;
	DeathBall* deathBall;                   //�f�X�{�[��
	GameClear* gameClear;                   //�Q�[���N���A
	SoundSource* gameBGM;		            //�Q�[������BGM�B
	Goal* goal;                             //�S�[��
	Toge* toge;                             //��
	Door* door;                             //�h�A
	Lever* lever;                           //���o�[
	Trap* trap;                             //�g���b�v
	Kabe* kabe;                             //��
	DeathCounter* deathCounter;             
	//MovingFloor* m_movingFloor = nullptr;
	Map* m_map = nullptr;                   //�}�b�v
	std::vector<Lever*>	m_leverVector;		//���o�[�̔z��B
	std::vector<Door*>	m_doorVector;		//�h�A�̔z��B
	float m_timer = 0.0f;
	float m_timer2 = 0.0f;
	float m_timer3 = 0.0f;
	float m_get = 0.0f;
};

