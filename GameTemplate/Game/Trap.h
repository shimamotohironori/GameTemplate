#pragma once
class Player;

class Trap:public IGameObject
{
public:
	Trap() {};
	~Trap();
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
	/*void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}*/

	Player* m_player=nullptr;//�v���C���[
	Vector3 m_position;   //���W
	Vector3 m_scale;
	CollisionObject* m_collisionObject=nullptr;              //�R���W�����I�u�W�F�N�g�B

	//Quaternion m_rotation;
	ModelRender m_modelRender;
};

