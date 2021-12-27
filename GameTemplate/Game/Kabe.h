#pragma once
class Kabe :public IGameObject
{
public:
	Kabe() {};
	~Kabe();
	bool Start();
    void Update ();
	//描画関数。
	void Render(RenderContext& rc);

	//座標。
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	// 大きさを設定する。
	void SetScale(Vector3 scale)
	{
		m_scale = scale;
	}

	//回転を設定する。
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

private:

	//モデルレンダ―。        
	ModelRender modelRender;
	//ゴーストオブジェクト。
	//PhysicsGhostObject m_physicsGhostObject;
	PhysicsStaticObject physicsStaticObject;
	ModelRender					m_modelRender;					//モデルレンダー。
	Vector3						m_position;						//座標。
	Vector3						m_scale = Vector3::miti;			//大きさ。
	//Vector3						m_scale;
	Quaternion					m_rotation;						//回転。
};

