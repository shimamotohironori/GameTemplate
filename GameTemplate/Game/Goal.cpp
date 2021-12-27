#include "stdafx.h"
#include "Goal.h"
#include "Player.h"
#include "Game.h"

bool Goal::Start()
{
	//�S�[��
	m_modelRender.Init("Assets/modelData/stage/Goal.tkm");
	//���W
/*	m_position.x = -6410.0f;
	m_position.y = 5.0f;
	m_position.z = -14793.0f;
*/
	//���W
	m_modelRender.SetPosition(m_position);
	//�傫��
	m_modelRender.SetScale(m_scale);
	//��]��ݒ肷��B
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	//�v���C���[��������
	m_player=FindGO<Player>("player");

	return true;
}

Goal::~Goal()
{

}

void Goal::Update()
{

	//Vector3 diff;
	//Vector3 playerPosition = m_player->position;
	//playerPosition.y += 30.0f;
	//�v���C���[����S�[���Ɍ������x�N�g�����v�Z�B
	Vector3 diff = m_player->position  - m_position;
	//�x�N�g���̒�����80.0f��菬����������B
	if (diff.Length() <= 80.0f)
	{
		m_player->goalCount += 1;
		//���g���폜����B
		//DeleteGO(this);

		/*SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1);
		se->Play(false);
		se->SetVolume(3.5f);*/
	}
	m_modelRender.Update();
}

void Goal::Render(RenderContext& rc)
{
	//���f����`�悷��B
	m_modelRender.Draw(rc);
}