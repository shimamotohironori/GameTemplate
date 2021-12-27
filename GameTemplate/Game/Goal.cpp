#include "stdafx.h"
#include "Goal.h"
#include "Player.h"
#include "Game.h"

bool Goal::Start()
{
	//ゴール
	m_modelRender.Init("Assets/modelData/stage/Goal.tkm");
	//座標
/*	m_position.x = -6410.0f;
	m_position.y = 5.0f;
	m_position.z = -14793.0f;
*/
	//座標
	m_modelRender.SetPosition(m_position);
	//大きさ
	m_modelRender.SetScale(m_scale);
	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	//プレイヤーを見つける
	m_player=FindGO<Player>("player");

	return true;
}

Goal::~Goal()
{

}

void Goal::Update()
{

	//Vector3 diff;
	//Vector3 playerPosition = m_player->position;
	//playerPosition.y += 30.0f;
	//プレイヤーからゴールに向かうベクトルを計算。
	Vector3 diff = m_player->position  - m_position;
	//ベクトルの長さが80.0fより小さかったら。
	if (diff.Length() <= 80.0f)
	{
		m_player->goalCount += 1;
		//自身を削除する。
		//DeleteGO(this);

		/*SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1);
		se->Play(false);
		se->SetVolume(3.5f);*/
	}
	m_modelRender.Update();
}

void Goal::Render(RenderContext& rc)
{
	//モデルを描画する。
	m_modelRender.Draw(rc);
}