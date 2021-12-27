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

	//座標を設定する
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	//大きさを設定する
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	//ドアの回転
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	Vector3 m_position;   //座標
	Player* m_player;//プレイヤー
	Vector3 m_scale;  //大きさ

	Quaternion m_rotation;
	ModelRender m_modelRender;
	//PhysicsStaticObject physicsStaticObject;
};

