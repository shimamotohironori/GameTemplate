#pragma once

//レバー//
//class CollisionObject;
class Lever : public IGameObject
{
public:
	//レバーステート
	enum EnLeverState {
		enLeverState_Idle,				//最初の待機状態。
		enLeverState_Push,				//押す。
		enLeverState_Push_Idle,			//押し終わった。
		enLeverState_Pull,				//引く。
		enLeverState_Pull_Idle			//引き終わった。
	};
public:
	Lever();
	~Lever();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//座標を設定する
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	//回転を設定する
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	//大きさを設定する
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	//レバーの番号を設定する
	void SetLeverNumber(const int leverNumber)
	{
		m_leverNumber = leverNumber;
	}
	//レバーの番号を取得する
	const int  GetLeverNumber() const
	{
		return m_leverNumber;
	}
private:
	//押すステートに移行する処理
	void ProcessTransitionPushState();
	//押し終わったステートに移行する処理
	void ProcessTransitionPushIdleState();
	//引くステートに移行する処理
	void ProcessTransitionPullState();
	//引き終わったステートに移行する処理
	void ProcessTransitionPullIdleState();
	//アニメーションを再生する処理
	void PlayAnimation();
	//ステート管理
	void ManageState();
	//待機状態のステート遷移処理。
	void ProcessIdleStateTransition();
	// 押すステートの遷移処理。
	void ProcessPushStateTransition();
	// 押し終わったステートの遷移処理。
	void ProcessPushIdleStateTransition();
	//引くステートの遷移処理。
	void ProcessPullStateTransition();
	//引き終わったステートの遷移処理。
	void ProcessPullIdleStateTransition();

	enum EnAnimationClip {          //アニメーション
		enAnimationClip_Idle,       //待機
		enAnimationClip_Push,       //押す
		enAnimationClip_Pull,       //引く
		enAnimationClip_Num,        //アニメーションの数
	};
	AnimationClip   m_animationClips[enAnimationClip_Num];
	ModelRender     m_modelRender;
	Vector3         m_position;
	Vector3         m_scale = Vector3::One;
	Quaternion      m_rotation;
	CollisionObject* m_collisionObject;              //コリジョンオブジェクト。
	EnLeverState    m_leverState = enLeverState_Idle;
	int             m_leverNumber = 0;
};

