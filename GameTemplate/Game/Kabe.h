#pragma once
class Kabe :public IGameObject
{
public:
	Kabe() {};
	~Kabe();
	bool Start();
    void Update ();
	//�`��֐��B
	void Render(RenderContext& rc);

	//���W�B
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	// �傫����ݒ肷��B
	void SetScale(Vector3 scale)
	{
		m_scale = scale;
	}

	//��]��ݒ肷��B
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

private:

	//���f�������_�\�B        
	ModelRender modelRender;
	//�S�[�X�g�I�u�W�F�N�g�B
	//PhysicsGhostObject m_physicsGhostObject;
	PhysicsStaticObject physicsStaticObject;
	ModelRender					m_modelRender;					//���f�������_�[�B
	Vector3						m_position;						//���W�B
	Vector3						m_scale = Vector3::miti;			//�傫���B
	//Vector3						m_scale;
	Quaternion					m_rotation;						//��]�B
};

