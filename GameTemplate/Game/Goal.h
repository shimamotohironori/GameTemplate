#pragma once
class Player;
class Goal : public IGameObject
{
public:
	Goal() {};
	~Goal();
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
	//�h�A�̉�]
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	Vector3 m_position;   //���W
	Player* m_player;//�v���C���[
	Vector3 m_scale;  //�傫��

	Quaternion m_rotation;
	ModelRender m_modelRender;
	//PhysicsStaticObject physicsStaticObject;
};

