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
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	//棘の番号を設定する
	void SetTogeNumber(const int togeNumber)
	{
		m_togeNumber = togeNumber;
	}
private:

	void ReleasePhysicsObject() {};        //フィジックスオブジェクトの当たり判定を開放する
	void CreatePhysicsObject() {};         //フィジックスオブジェクトの当たり判定を作成する

	Vector3 m_position;   //座標
	Player* m_player;//プレイヤー
	Vector3 m_scale;
	Vector3 Position; //初期座標
	//PhysicsStaticObject m_physicsStaticObject;            //フィジクススタティックオブジェクト
	//CharacterController m_charaCon;  //キャラクターコントローラー
	Quaternion m_rotation;
	ModelRender m_modelRender;
	int m_togeNumber;
	CollisionObject* m_collisionObject;
};

