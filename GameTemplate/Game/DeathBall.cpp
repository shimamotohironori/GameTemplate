#include "stdafx.h"
#include "DeathBall.h"
#include "Player.h"
#include "Enemy.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
//#include <random>

bool DeathBall::Start()
{
	//�f�X�{�[���̏�ԁB
	m_modelRender.Init("Assets/modelData/stage/DeathBall.tkm");
	//m_modelRender.Init("Assets/modelData/stage/DieBall.tkm");
	m_modelRender.SetScale({ 2.0f,2.0f, 2.0f });
	/*//�����𐶐�
	constexpr int MIN = -790;//�����͈͍̔Œ�l
	constexpr int MAX = 790;//�����͈͍̔ő�l
	constexpr int RAND_NUMS_TO_GENERATE = 2;//�����𐶐������*/

	//�f�X�{�[���̗����B
	/*std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> distr(MIN, MAX);
	for (int n = 0; n < RAND_NUMS_TO_GENERATE; ++n) {
		switch (n) {
		case 0:
			m_position.x = distr(eng);
			break;
		case 1:
			m_position.z = distr(eng);
			break;
		}
	}*/
	//m_position.y = 2600.0f;
	//m_position.y = 100.0f;
	//m_position.z = 12.0f;
	m_modelRender.SetPosition(Position);
	m_modelRender.Update();


	//�R���C�_�[���������B
	m_sphereCollider.Create(55.0f);

	//���̂��������B
	RigidBodyInitData rbInitData;
	//����(�d��)��ݒ肷��B
	rbInitData.mass = 10.0f;
	//�R���C�_�[��ݒ肷��B
	rbInitData.collider = &m_sphereCollider;
	//���W��ݒ肷��B
	rbInitData.pos = Position;
	//��]�̂��₷����ݒ肷��B0�`1
	rbInitData.localInteria.Set(
		0.5f,
		0.5f,
		0.5f
	);
	//�����͂�ݒ肷��B
	//���l��傫������ƁA���˕Ԃ肪�傫���Ȃ�B
	//PhysicsStaticObject�ɂ������͂�ݒ肷��K�v������(Game.cpp�Q��)�B
	rbInitData.restitution = 1.0f;
	//���̂��������B
	m_rigidBody.Init(rbInitData);
	//���C�͂�ݒ肷��B0�`10�܂ŁB
	m_rigidBody.SetFriction(0.0f);
	//���`�ړ�����v�f��ݒ肷��B
	//0���w�肵�����͈ړ����Ȃ��B
	//�Ⴆ��y��0�Ɏw�肷��ƁAy���W�͈ړ����Ȃ��Ȃ�B
	m_rigidBody.SetLinearFactor(1.0f, 1.0f, 1.0f);

	player = FindGO<Player>("player");  //�v���C���[��������B

	enemy = FindGO<Enemy>("enemy");     //�G�l�~�[��������B

	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/boll.wav");  //���ʉ�
		
	//�S�[�X�g�I�u�W�F�N�g���������B
	//Quaternion rot;
	//m_physicsGhostObject.CreateSphere(m_position,rot, 20.0f);
	Vector3 force = { 900.0f,00.0f,900.0f };
	m_rigidBody.AddForce(
		force,		//��
		g_vec3Zero	//�͂������鍄�̂̑��Έʒu
	);
	return true;
}



void DeathBall::Update()
{

	Vector3 pos;
	Vector3 enemy;
	Quaternion rot;
	//���̂̍��W�Ɖ�]���擾�B
	m_rigidBody.GetPositionAndRotation(pos, rot);
	//���̂̍��W�Ɖ�]�����f���ɔ��f�B
	m_modelRender.SetPosition(pos);
	m_modelRender.SetRotation(rot);
	//���̂ɗ͂�������B
	Vector3 force = { 0.0f,-5000.0f,0.0f };
	m_rigidBody.AddForce(
		force,		//��
		g_vec3Zero	//�͂������鍄�̂̑��Έʒu
	);

	Vector3 vector = player->position;
	vector.y += 30.0f;
	//�v���C���[����f�X�{�[���Ɍ������x�N�g�����v�Z�B
	diff = vector - pos;
	//�x�N�g���̒�����120.0f��菬����������B
	if (diff.Length() <= 120.0f)
	{
		player->deathBallCount += 1;
		//���g���폜����B
		//DeleteGO(this);
	}



	//���f���̍X�V�����B
	m_modelRender.Update();

}



void DeathBall::Render(RenderContext& rc)
{
	//���f����`�悷��B
	m_modelRender.Draw(rc);
	m_fontRender.Draw(rc);
}