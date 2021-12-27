#pragma once

//ドア//

class Door : public IGameObject
{
public:
	//ドアステート。
	enum EnDoorState {
		enDoorState_Idle,				//待機。
		enDoorState_Open,				//オープン。
		enDoorState_Open_Idle,			//オープンし終わった。
		enDoorState_Close,				//クローズ。
		enDoorState_Close_Idle			//クローズし終わった。
	};
public:
	Door();
	~Door();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void NotifyOpen(); //扉が開く
	void NotifyClose();//扉が閉まる

	//ドアの座標
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	//ドアの回転
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	//ドアの大きさ
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	//ドアの番号
	void SetDoorNumber(const int doorNumber)
	{
		m_doorNumber = doorNumber;
	}

	//ドアの番号を取得する
	const int GetDoorNumber() const
	{
		return m_doorNumber;
	}
private:
	void PlayAnimation();               //アニメーションの再生
	void ReleasePhysicsObject();        //フィジックスオブジェクトの当たり判定を開放する
	void CreatePhysicsObject();         //フィジックスオブジェクトの当たり判定を作成する
	void ManageState();                 //ステート管理。
	void ProcessOpenStateTransition();  //オープンステートのステート遷移処理
	void ProcessCloseStateTransition(); //クローズステートのステート遷移処理
private:
	ModelRender m_modelRender;
	Vector3 m_position;
	Quaternion m_rotation;
	Vector3 m_scale = Vector3::One;
	enum EnAnimationClip {           //アニメーション
		enAnimationClip_Idle,        //待機
		enAnimationClip_Open,        //開く
		enAnimationClip_Close,       //閉じる
		enAnimationClip_Num,         //アニメーションの数
	};
	AnimationClip       m_animationClips[enAnimationClip_Num];   //アニメーションクリップ
	PhysicsStaticObject m_physicsStaticObject;                    //フィジクススタティックオブジェクト
	EnDoorState         m_doorState = enDoorState_Idle;          //ドアのステート
	int                 m_doorNumber = 0;                        //ドアの番号     
};

