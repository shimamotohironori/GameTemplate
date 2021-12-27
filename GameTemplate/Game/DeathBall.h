#pragma once
#include "sound/SoundSource.h"
class Player;
class Enemy;
class DeathBall:public IGameObject
{
public:
	bool Start()override;
	void Render(RenderContext& rc)override;
	void Update()override;

	//���f�������_�\�B        
	ModelRender m_modelRender;
	SphereCollider m_sphereCollider;//�~�^�̃R���C�_�[�B
	RigidBody m_rigidBody;
	//Vector3 m_position;  //���W�B
	Vector3 position; //���W
	Vector3 diff = Vector3::One * 100.0f;
	Player* player;//�v���C���[
	Enemy* enemy;//�G�l�~�[
	Vector3 Position; //�������W
	//�S�[�X�g�I�u�W�F�N�g�B
	//PhysicsGhostObject m_physicsGhostObject;
	SoundSource* se;
	FontRender m_fontRender; //����
	float m_get = 0.0f;
};

