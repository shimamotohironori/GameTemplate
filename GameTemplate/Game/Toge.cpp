#include "stdafx.h"
#include "Toge.h"
#include "Player.h"
#include "Game.h"
#include <random>

bool Toge::Start()
{
	//棘
	m_modelRender.Init("Assets/modelData/stage/toge.tkm");
	//座標
	m_modelRender.SetPosition(m_position);
	//大きさ
    //m_modelRender.SetScale({ 2.0f,3.0f, -4.0f });
	m_modelRender.SetScale(m_scale);
	//回転
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	//当たり判定を作成する。
	//m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	//g_soundEngine->ResistWaveFileBank(6, "Assets/sound/toge.wav");  //効果音

	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);

	Vector3 collisionPosition = m_position;
	//座標をプレイヤーの少し前に設定する。
	//collisionPosition += m_forward * 50.0f;
	//collisionPosition.y += 100.0f;
	if (m_togeNumber == 1)
	{
		collisionPosition.z -= 250.0f;
		m_collisionObject->CreateBox(collisionPosition,                   //座標。
			Quaternion::Identity,                                      //回転。
			Vector3(235.0f, 235.0f, -500.0f)                              //大きさ。
		);
		m_collisionObject->SetPosition(collisionPosition);
		m_collisionObject->SetName("TOGE");

	}
	else
	{
		collisionPosition.z += 250.0f;
		m_collisionObject->CreateBox(collisionPosition,                   //座標。
			Quaternion::Identity,                                      //回転。
			Vector3(235.0f, 235.0f, -500.0f)                              //大きさ。
		);
		m_collisionObject->SetPosition(collisionPosition);
		m_collisionObject->SetName("TOGE");
	}

	m_collisionObject->SetIsEnableAutoDelete(false);

	//プレイヤーを見つける
	m_player = FindGO<Player>("player");

	return true;
}

Toge::~Toge()
{
	DeleteGO(m_collisionObject);
}

void Toge::Update()
{
	
	//ボックス状のコリジョンを作成する。
	
	
	//collisionObject->Update();

/*	//プレイヤーから棘に向かうベクトルを計算。
	Vector3 diff = m_player->position - m_position;
	//ベクトルの長さが300.0fより小さかったら。
	if (diff.Length() <= 300.0f)
	{
		m_player->togeCount += 1;
		//自身を削除する。
		DeleteGO(this);
		
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(6);
		se->Play(false);
		se->SetVolume(1.0f);
		
	}
*/
	m_modelRender.Update();
}

//フィジックスオブジェクトの当たり判定の解放
/*void Toge::ReleasePhysicsObject()
{
	m_physicsStaticObject.Release();
}*/
//フィジックスオブジェクトの当たり判定の生成
/*void Toge::CreatePhysicsObject()
{
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}*/

void Toge::Render(RenderContext& rc)
{
	//モデルを描画する。
	m_modelRender.Draw(rc);
}