#pragma once
class Player;
class Enemy:public IGameObject
{
public:
	void Init(Vector3 initPos);
	bool Start();
	void Update();
	void Move();
	void Rotation();
	void Render(RenderContext& rc);
	void Chase();//�ǐՏ����B
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	const bool SearchPlayer() const;//�v���C���[������������true�B
	CharacterController m_charaCon;  //�L�����N�^�[�R���g���[���[
	Vector3 position; 
	Vector3 Position; //�������W
	//Vector3 m_diff = Vector3::One * 100.0f;
	ModelRender m_modelRender;	// ���f�������_���[�B
	
	Vector3 m_position;			// ���W�B
	Vector3	m_moveSpeed;		//�ړ����x
	Vector3 m_forward = Vector3::AxisZ; //�G�l�~�[�̐��ʃx�N�g���B
	Quaternion m_rotation;		// ��]�B
	Player* player = nullptr;	// �v���C���[�̃A�h���X���L������ϐ��B
	Player* m_player;
	float m_get = 0.0f;
	Quaternion rot;
};

