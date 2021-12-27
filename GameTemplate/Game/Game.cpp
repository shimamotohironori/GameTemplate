#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Title.h"
#include "Player.h"
#include "Enemy.h"
#include "GameCamera.h"
#include"DeathBall.h"
#include "GameOver.h"
#include "Lever.h"
#include "Door.h"
#include "GameClear.h"
#include "sound/SoundEngine.h"
#include "Goal.h"
#include "Toge.h"
#include "Trap.h"
#include "Kabe.h"
#include "DeathCounter.h"
#include "Map.h"
#include "MovingFloor.h"

namespace
{
	Vector3 BACKGROUND_SCALE = Vector3(0.7f, 1.0f, 0.7f);
}

void Game::BALL()
{
	//�f�X�{�[��
	deathBall = NewGO<DeathBall>(0, "deathBall");
	deathBall->position = { -2000.0f,1000.0f,12.0f };
	deathBall->Position = deathBall->position;

/*	DeathBall* deathBall2 = NewGO<DeathBall>(0, "deathBall");
	deathBall2->position = { -4000.0f,1500.0f,40.0f };
	deathBall2->Position = deathBall2->position;

	DeathBall* deathBall3 = NewGO<DeathBall>(0, "deathBall");
	deathBall3->position = { -6000.0f,2600.0f,60.0f };
	deathBall3->Position = deathBall3->position;

	DeathBall* deathBall4 = NewGO<DeathBall>(0, "deathBall");
	deathBall4->position = { -8000.0f,2600.0f,60.0f };
	deathBall4->Position = deathBall3->position;

	DeathBall* deathBall5 = NewGO<DeathBall>(0, "deathBall");
	deathBall5->position = { -10000.0f,2600.0f,60.0f };
	deathBall5->Position = deathBall3->position;

	DeathBall* deathBall6 = NewGO<DeathBall>(0, "deathBall");
	deathBall6->position = { -7450.0f,2600.0f,7.0f };
	deathBall6->Position = deathBall3->position;
	/*
	DeathBall* deathBall7 = NewGO<DeathBall>(0, "deathBall");
	deathBall7->position = { -10000.0f,2600.0f,60.0f };
	deathBall7->Position = deathBall3->position;*/
}

Game::~Game()
{
	//�g���b�v�̍폜�B
	//DeleteGO(trap);

	//�G�l�~�[�̍폜�B
	DeleteGO(enemy);
	//�Q�[���J�����̍폜�B
	DeleteGO(gameCamera);
	//�w�i�̍폜�B
	const auto& backGrounds = FindGOs<BackGround>("backGround");
	for (auto& backGround : backGrounds)
	{
		DeleteGO(m_backGround);
	}

	//�Q�[��BGM�̍폜�B
	DeleteGO(gameBGM);
	//�S�[���̍폜�B
	DeleteGO(goal);
	//�ǂ̍폜�B
	DeleteGO(kabe);
	//�h�A�̍폜�B
	DeleteGO(door);
	//���o�[�̍폜�B
	DeleteGO(lever);

	//���̍폜�B
	const auto& toges = FindGOs<Toge>("toge");
	for (auto toge : toges)
	{
		DeleteGO(toge);
	}


	//DeleteGO(deathBall);
	const auto& deathBalls = FindGOs<DeathBall>("deathBall");
	for (auto deathBall : deathBalls)
	{
		//�f�X�{�[�����폜����B
		DeleteGO(deathBall);
	}

	//�v���C���[�̍폜�B
	DeleteGO(player);

}

bool Game::Start()
{
	//�v���C���[�̐����B
	player = NewGO<Player>(0,"player");
	//�G�l�~�[�̐����B
	enemy = NewGO<Enemy>(0, "enemy");
	enemy->m_position = { 20000.0f, 30.0f, 30.0f };//�G�l�~�[�̍��W�B
	//�Q�[���J�����̐����B
	gameCamera = NewGO<GameCamera>(0, "gameCamera");

	BALL();


 //���x�����\�z����B
	
	m_levelRender.Init("Assets/levelData/BackGround5.tkl",
		[&](LevelObjectData& objData)
		{
			//���O��backGround��������B
			if (objData.EqualObjectName(L"stage3") == true) {
				//�w�i�I�u�W�F�N�g���쐬����B
				m_backGround = NewGO<BackGround>(0, "backGround");
				//���W��ݒ肷��B
				m_backGround->SetPosition(objData.position);
				//�傫����ݒ肷��B
				m_backGround->SetScale(objData.scale);
				//��]��ݒ肷��B
				m_backGround->SetRotation(objData.rotation);
				return true;
			}
			
			//���O��Goal��������
			else if (objData.EqualObjectName(L"Goal") == true) {
				//�w�i�I�u�W�F�N�g���쐬����B
				auto goal = NewGO<Goal>(0, "goal");
				//���W��ݒ肷��B
				goal->SetPosition(objData.position);
				//�傫����ݒ肷��B
				goal->SetScale(objData.scale);
				//��]��ݒ肷��B
				goal->SetRotation(objData.rotation);
				return true;
			}
			
			//���O��kabe��������
			else if (objData.EqualObjectName(L"kabe") == true) {
				//�w�i�I�u�W�F�N�g���쐬����B
				auto kabe = NewGO<Kabe>(0, "kabe");
				//���W��ݒ肷��B
				kabe->SetPosition(objData.position);
				//�傫����ݒ肷��B
				kabe->SetScale(objData.scale);
				//��]��ݒ肷��B
				kabe->SetRotation(objData.rotation);
				return true;
			}
			//���O��Trap��������
			/*else if (objData.EqualObjectName(L"Trap") == true) {
				//�w�i�I�u�W�F�N�g���쐬����B
				auto trap = NewGO<Trap>(0, "trap");
				//���W��ݒ肷��B
				trap->SetPosition(objData.position);
				//�傫����ݒ肷��B
				trap->SetScale(objData.scale);
				//��]��ݒ肷��B
				//goal->SetRotation(objData.rotation);
				return true;
			}*/

			//���O��toge��������
			else if (objData.ForwardMatchName(L"toge") == true) {
				//�w�i�I�u�W�F�N�g���쐬����B
				auto toge = NewGO<Toge>(0, "toge");
				//���W��ݒ肷��B
				toge->SetPosition(objData.position);
				//�傫����ݒ肷��B
				toge->SetScale(objData.scale);
				//��]��ݒ肷��B
				toge->SetRotation(objData.rotation);
				//�ԍ���ݒ肷��B
				toge->SetTogeNumber(objData.number);
				return true;
			}

			//���O��lever��������B
			else if (objData.ForwardMatchName(L"lever") == true)
			{
				//���o�[�̃I�u�W�F�N�g���쐬����B
				auto lever = NewGO<Lever>(0, "lever");
				//���W��ݒ肷��B
				lever->SetPosition(objData.position);
				//�傫����ݒ肷��B
				lever->SetScale(objData.scale);
				//��]��ݒ肷��B
				lever->SetRotation(objData.rotation);
				//���o�[�̔z�u�ɍ쐬�����I�u�W�F�N�g��������B
				m_leverVector.push_back(lever);
				//�ԍ���ݒ肷��B
				lever->SetLeverNumber(objData.number);
				return true;
			}

			//���O��door��������B
			else if (objData.ForwardMatchName(L"door") == true)
			{
				//�h�A�̃I�u�W�F�N�g���쐬����B
				auto door = NewGO<Door>(0, "door");
				//���W��ݒ肷��B
				door->SetPosition(objData.position);
				//�傫����ݒ肷��B
				door->SetScale(objData.scale);
				//��]��ݒ肷��B
				door->SetRotation(objData.rotation);
				//�ԍ���ݒ肷��B
				door->SetDoorNumber(objData.number);
				//�h�A�̔z�u�ɍ쐬�����I�u�W�F�N�g��������B
				m_doorVector.push_back(door);
				
				return true;
			}

			return true;
		});

		//�}�b�v�̍쐬
		//m_map = NewGO<Map>(0, "Map");
		

	//�����蔻��L����
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	SkyCube* m_skycube = NewGO<SkyCube>(0,"skycube");
	//m_skycube.SetScale({ 8.0f,8.0f, 12.0f });

	//�Q�[������BGM��ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/gamebgm3.wav");
	//�Q�[������BGM���Đ�����B
	gameBGM = NewGO<SoundSource>(0);
	gameBGM->Init(2);
	gameBGM->Play(true);
	gameBGM->SetVolume(0.2f);



	m_spriteRender.Init("Assets/sprite/MAP.dds", 512.0f, 720.0f);
	m_spriteRender.Update();

	return true;
}

void Game::Update()
{
	//�}�b�v�����u��
	m_spriteRender.SetPosition({ 670.0f,200.0f,0.0f });
	m_spriteRender.Update();
	//����
	m_timer += g_gameTime->GetFrameDeltaTime();
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%d�b�o��!!", int(m_timer));

	//�\������e�L�X�g��ݒ�B
	m_fontRender2.SetText(wcsbuf);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender2.SetPosition(Vector3(-200.0f, 500.0f, 2000.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender2.SetScale(2.0f);
	//�t�H���g�̐F��ݒ�B
	m_fontRender2.SetColor(g_vec4Black);

	
	//m_modelRender.Update();

	m_timer2 += g_gameTime->GetFrameDeltaTime();
	//100�b��������Q�[���I�[�o�[
	if (m_timer2 >= 100.0f)
	{
		NewGO<GameOver>(0, "gameOver");
		DeleteGO(this);
	}
	

	
	//���낢�듖��������Q�[���I�[�o�[�B
	if (player->deathBallCount == 1||
		player->togeCount == 1||
		player->enemyCount == 1)
	{
		NewGO<GameOver>(0, "gameOver");
		DeleteGO(this);
	}
	if (player->goalCount == 1)//�S�[���ɂ���������Q�[���N���A�B
	{
		NewGO<GameClear>(0, "gameClear");
		DeleteGO(this);
	}
	
	//�v���C���[��y�̍��W��-500�ȉ��ɂȂ����炰�[�ނ��[�΁[
	if (FindGO<Player>("player")->position.y <= -500.0f)
	{
		NewGO<GameOver>(0, "gameOver");
		DeleteGO(this);
	}

}

void Game::Render(RenderContext& rc)
{
	//m_modelRender.Draw(rc);
	m_spriteRender.Draw(rc);
	//m_fontRender.Draw(rc);
	m_fontRender2.Draw(rc);
}