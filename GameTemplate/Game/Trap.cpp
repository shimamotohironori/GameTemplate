#include "stdafx.h"
#include "Trap.h"
#include "Game.h"
#include "Player.h"
#include "collision/CollisionObject.h"

namespace
{
	Vector3 COLLISION_HEIGHT = Vector3(0.0f, 1.5f, 0.0f);
	Vector3  COLLISION_SIZE = Vector3(770.0f, 5.0f, 1620.0f);
}

bool Trap::Start()
{
	//トラップ
	m_modelRender.Init("Assets/modelData/stage/Trap.tkm");
	//座標
	m_modelRender.SetPosition(m_position);
	//大きさ
	//m_modelRender.SetScale({ 2.0f,3.0f, -4.0f });
	m_modelRender.SetScale(m_scale);
	//回転
	//m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();



	m_collisionObject = NewGO<CollisionObject>(0, "collisionobject");
	//コリジョンオブジェクトを。
	//動く床の上に設置する(キャラクターが上に乗ったら反応するようにしたいため)。
	m_collisionObject->CreateBox(
		m_position + COLLISION_HEIGHT,
		Quaternion::Identity,
		COLLISION_SIZE
	);
	m_collisionObject->SetIsEnableAutoDelete(false);


	return true;
}

Trap::~Trap()
{
	DeleteGO(m_collisionObject);
}

void Trap::Update()
{
	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが。
     //衝突したら。(キャラクターが動く床の上に乗ったら)。
	if (m_collisionObject->IsHit(FindGO<Player>("player")->m_charaCon) == true)
	{
		DeleteGO(this);

		/*
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1);
		se->Play(false);
		se->SetVolume(3.5f);
		*/
	}
	/*
	//プレイヤーからゴールに向かうベクトルを計算。
	Vector3 diff = m_player->position - m_position;
	//ベクトルの長さが80.0fより小さかったら。
	if (diff.Length() <= 80.0f)
	{
		m_player->trapCount += 1;
		//自身を削除する。
		DeleteGO(this);

		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1);
		se->Play(false);
		se->SetVolume(3.5f);
	}*/
	m_modelRender.Update();
}

void Trap::Render(RenderContext& rc)
{
	//モデルを描画する。
	m_modelRender.Draw(rc);
}