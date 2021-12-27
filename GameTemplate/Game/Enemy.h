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
	void Chase();//追跡処理。
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	const bool SearchPlayer() const;//プレイヤーが見つかったらtrue。
	CharacterController m_charaCon;  //キャラクターコントローラー
	Vector3 position; 
	Vector3 Position; //初期座標
	//Vector3 m_diff = Vector3::One * 100.0f;
	ModelRender m_modelRender;	// モデルレンダラー。
	
	Vector3 m_position;			// 座標。
	Vector3	m_moveSpeed;		//移動速度
	Vector3 m_forward = Vector3::AxisZ; //エネミーの正面ベクトル。
	Quaternion m_rotation;		// 回転。
	Player* player = nullptr;	// プレイヤーのアドレスを記憶する変数。
	Player* m_player;
	float m_get = 0.0f;
	Quaternion rot;
};

