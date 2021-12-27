#include "stdafx.h"
#include "Door.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Door::Door()
{

}

Door::~Door()
{

}

bool Door::Start()
{
	//アニメーションを読み込む。
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/door/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Open].Load("Assets/animData/door/open.tka");
	m_animationClips[enAnimationClip_Open].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Close].Load("Assets/animData/door/close.tka");
	m_animationClips[enAnimationClip_Close].SetLoopFlag(false);
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/door/door.tkm", m_animationClips, enAnimationClip_Num);
	//座標を設定する。
	m_modelRender.SetPosition(m_position);
	//大きさを設定する。
	m_modelRender.SetScale(m_scale);
	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);

	//モデルの更新。
	m_modelRender.Update();
	//当たり判定を作成する。
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	//音を読み込む。
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/door_cut.wav");

	return true;
}

void Door::Update()
{
	//アニメーションを再生する。
	PlayAnimation();
	//ステート管理。
	ManageState();

	//モデルの更新。
	m_modelRender.Update();
}

//ドアが開きます
void Door::NotifyOpen()
{
	//オープンステートに遷移する
	m_doorState = enDoorState_Open;
}


//ドアが閉じます
void Door::NotifyClose()
{
	//クローズステートに遷移する
	m_doorState = enDoorState_Close;
}

//ドアのアニメーション
void Door::PlayAnimation()
{
	switch (m_doorState)
	{
		//待機ステートの時。
	case enDoorState_Idle:
		//待機アニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
		//オープンステートの時。
	case enDoorState_Open:
		//オープンアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Open);
		m_modelRender.SetAnimationSpeed(0.6f);
		break;
		//クローズステートの時。
	case enDoorState_Close:
		//クローズアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Close);
		m_modelRender.SetAnimationSpeed(0.6f);
		break;
	default:
		break;
	}
}


//フィジックスオブジェクトの当たり判定の解放
void Door::ReleasePhysicsObject()
{
	m_physicsStaticObject.Release();
}
//フィジックスオブジェクトの当たり判定の生成
void Door::CreatePhysicsObject()
{
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

//ドアが開くアニメーション
void Door::ProcessOpenStateTransition()
{
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		ReleasePhysicsObject();
		m_doorState = enDoorState_Open_Idle;
	}
}

//ドアが閉じるアニメーション
void Door::ProcessCloseStateTransition()
{
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		CreatePhysicsObject();
		m_doorState = enDoorState_Close_Idle;
	}
}

//ステート管理
void Door::ManageState()
{
	switch (m_doorState)
	{
		//待機ステートの時。
	case Door::enDoorState_Idle:

		break;
		//オープンステートの時。
	case Door::enDoorState_Open:
		//オープンステートのステート遷移処理。
		ProcessOpenStateTransition();
		break;
		//オープン終わりステートの時。
	case Door::enDoorState_Open_Idle:

		break;
		//クローズステートの時。
	case Door::enDoorState_Close:
		//クローズステートのステート遷移処理。
		ProcessCloseStateTransition();
		break;
		//クローズ終わりステートの時。
	case Door::enDoorState_Close_Idle:

		break;
	default:
		break;
	}
}

void Door::Render(RenderContext& rc)
{
	//モデルを描画する
	m_modelRender.Draw(rc);
}