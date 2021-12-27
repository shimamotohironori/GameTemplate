#include "stdafx.h"
#include "Trap.h"
#include "Game.h"
#include "Player.h"
#include "collision/CollisionObject.h"

namespace
{
	Vector3 COLLISION_HEIGHT = Vector3(0.0f, 1.5f, 0.0f);
	Vector3  COLLISION_SIZE = Vector3(770.0f, 5.0f, 1620.0f);
}

bool Trap::Start()
{
	//�g���b�v
	m_modelRender.Init("Assets/modelData/stage/Trap.tkm");
	//���W
	m_modelRender.SetPosition(m_position);
	//�傫��
	//m_modelRender.SetScale({ 2.0f,3.0f, -4.0f });
	m_modelRender.SetScale(m_scale);
	//��]
	//m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();



	m_collisionObject = NewGO<CollisionObject>(0, "collisionobject");
	//�R���W�����I�u�W�F�N�g���B
	//�������̏�ɐݒu����(�L�����N�^�[����ɏ�����甽������悤�ɂ���������)�B
	m_collisionObject->CreateBox(
		m_position + COLLISION_HEIGHT,
		Quaternion::Identity,
		COLLISION_SIZE
	);
	m_collisionObject->SetIsEnableAutoDelete(false);


	return true;
}

Trap::~Trap()
{
	DeleteGO(m_collisionObject);
}

void Trap::Update()
{
	//�R���W�����I�u�W�F�N�g�ƃv���C���[�̃L�����N�^�[�R���g���[���[���B
     //�Փ˂�����B(�L�����N�^�[���������̏�ɏ������)�B
	if (m_collisionObject->IsHit(FindGO<Player>("player")->m_charaCon) == true)
	{
		DeleteGO(this);

		/*
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1);
		se->Play(false);
		se->SetVolume(3.5f);
		*/
	}
	/*
	//�v���C���[����S�[���Ɍ������x�N�g�����v�Z�B
	Vector3 diff = m_player->position - m_position;
	//�x�N�g���̒�����80.0f��菬����������B
	if (diff.Length() <= 80.0f)
	{
		m_player->trapCount += 1;
		//���g���폜����B
		DeleteGO(this);

		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1);
		se->Play(false);
		se->SetVolume(3.5f);
	}*/
	m_modelRender.Update();
}

void Trap::Render(RenderContext& rc)
{
	//���f����`�悷��B
	m_modelRender.Draw(rc);
}