#pragma once
class Player;
class Toge :public IGameObject
{
public:
	Toge() {};
	~Toge();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//���W��ݒ肷��
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	//�傫����ݒ肷��
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	//��]
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	//���̔ԍ���ݒ肷��
	void SetTogeNumber(const int togeNumber)
	{
		m_togeNumber = togeNumber;
	}
private:

	void ReleasePhysicsObject() {};        //�t�B�W�b�N�X�I�u�W�F�N�g�̓����蔻����J������
	void CreatePhysicsObject() {};         //�t�B�W�b�N�X�I�u�W�F�N�g�̓����蔻����쐬����

	Vector3 m_position;   //���W
	Player* m_player;//�v���C���[
	Vector3 m_scale;
	Vector3 Position; //�������W
	//PhysicsStaticObject m_physicsStaticObject;            //�t�B�W�N�X�X�^�e�B�b�N�I�u�W�F�N�g
	//CharacterController m_charaCon;  //�L�����N�^�[�R���g���[���[
	Quaternion m_rotation;
	ModelRender m_modelRender;
	int m_togeNumber;
	CollisionObject* m_collisionObject;
};

