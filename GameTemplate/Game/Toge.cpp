#include "stdafx.h"
#include "Toge.h"
#include "Player.h"
#include "Game.h"
#include <random>

bool Toge::Start()
{
	//��
	m_modelRender.Init("Assets/modelData/stage/toge.tkm");
	//���W
	m_modelRender.SetPosition(m_position);
	//�傫��
    //m_modelRender.SetScale({ 2.0f,3.0f, -4.0f });
	m_modelRender.SetScale(m_scale);
	//��]
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	//�����蔻����쐬����B
	//m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	//g_soundEngine->ResistWaveFileBank(6, "Assets/sound/toge.wav");  //���ʉ�

	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);

	Vector3 collisionPosition = m_position;
	//���W���v���C���[�̏����O�ɐݒ肷��B
	//collisionPosition += m_forward * 50.0f;
	//collisionPosition.y += 100.0f;
	if (m_togeNumber == 1)
	{
		collisionPosition.z -= 250.0f;
		m_collisionObject->CreateBox(collisionPosition,                   //���W�B
			Quaternion::Identity,                                      //��]�B
			Vector3(235.0f, 235.0f, -500.0f)                              //�傫���B
		);
		m_collisionObject->SetPosition(collisionPosition);
		m_collisionObject->SetName("TOGE");

	}
	else
	{
		collisionPosition.z += 250.0f;
		m_collisionObject->CreateBox(collisionPosition,                   //���W�B
			Quaternion::Identity,                                      //��]�B
			Vector3(235.0f, 235.0f, -500.0f)                              //�傫���B
		);
		m_collisionObject->SetPosition(collisionPosition);
		m_collisionObject->SetName("TOGE");
	}

	m_collisionObject->SetIsEnableAutoDelete(false);

	//�v���C���[��������
	m_player = FindGO<Player>("player");

	return true;
}

Toge::~Toge()
{
	DeleteGO(m_collisionObject);
}

void Toge::Update()
{
	
	//�{�b�N�X��̃R���W�������쐬����B
	
	
	//collisionObject->Update();

/*	//�v���C���[���瞙�Ɍ������x�N�g�����v�Z�B
	Vector3 diff = m_player->position - m_position;
	//�x�N�g���̒�����300.0f��菬����������B
	if (diff.Length() <= 300.0f)
	{
		m_player->togeCount += 1;
		//���g���폜����B
		DeleteGO(this);
		
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(6);
		se->Play(false);
		se->SetVolume(1.0f);
		
	}
*/
	m_modelRender.Update();
}

//�t�B�W�b�N�X�I�u�W�F�N�g�̓����蔻��̉��
/*void Toge::ReleasePhysicsObject()
{
	m_physicsStaticObject.Release();
}*/
//�t�B�W�b�N�X�I�u�W�F�N�g�̓����蔻��̐���
/*void Toge::CreatePhysicsObject()
{
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}*/

void Toge::Render(RenderContext& rc)
{
	//���f����`�悷��B
	m_modelRender.Draw(rc);
}