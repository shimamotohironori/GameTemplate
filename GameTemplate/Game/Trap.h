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
	//回転
	/*void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}*/

	Player* m_player=nullptr;//プレイヤー
	Vector3 m_position;   //座標
	Vector3 m_scale;
	CollisionObject* m_collisionObject=nullptr;              //コリジョンオブジェクト。

	//Quaternion m_rotation;
	ModelRender m_modelRender;
};

