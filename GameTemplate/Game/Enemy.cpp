#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include <time.h>
#include <random>

bool Enemy::Start()
{
	m_modelRender.Init("Assets/modelData/enemy.tkm");
	m_modelRender.SetRotation(m_rotation);
	rot.SetRotationDegY(-90.0f);
	//乱数を生成
	/*constexpr int MIN = -790;//乱数の範囲最低値
	constexpr int MAX = 790;//乱数の範囲最大値
	constexpr int RAND_NUMS_TO_GENERATE = 2;//乱数を生成する回数

	//エネミーの乱数。
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> distr(MIN, MAX);
	for (int n = 0; n < RAND_NUMS_TO_GENERATE; ++n) {
		switch (n) {
		case 0:
			m_position.x = distr(eng);
			break;
		case 1:
			m_position.z = distr(eng);
			break;
		}
	}*/
	//m_modelRender.SetPosition(m_position);
	/*m_position.x = 8400.0f;
	m_position.y = 30.0f;
	m_position.z = 0.0f;*/
	m_modelRender.SetScale({ 2.0f, 2.0f, 2.0f });
	m_modelRender.Update();
	m_charaCon.Init(40.0f, 40.0f, m_position);//キャラコンの作成。半径・高さ・座標

	m_player = FindGO<Player>("player");  //プレイヤーを見つける。

	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/hi.efk");

	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	return true;
}

void Enemy::Update()
{

	Vector3 diff;
	Vector3 playerPosition = m_player->position;
	playerPosition.y += 30.0f;
	//プレイヤーからエネミーに向かうベクトルを計算。
	diff = playerPosition - m_position;
	//ベクトルの長さが120.0fより小さかったら。
	if (diff.Length() <= 80.0f)
	{
		m_player->enemyCount += 1;
		//自身を削除する。
		DeleteGO(this);

		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->Init(0);
		effectEmitter->SetScale({ 6.0f,6.0f,6.0f });
		effectEmitter->SetPosition(m_position);
		effectEmitter->Play();
		/*SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1);
		se->Play(false);
		se->SetVolume(3.5f);*/
	}
	//Move();
	Rotation();
	m_modelRender.Update();
}

void Enemy::Move()
{

	Vector3 playerPosition = m_player->GetPosition();
	Vector3 diff = playerPosition - m_position;
	diff.Normalize();
	m_moveSpeed = diff * 20.0f;
	//m_moveSpeed.y = 0.0f;
	m_position = m_charaCon.Execute(m_moveSpeed, 10.0f / 10.0f);
	
	m_modelRender.SetPosition(m_position);
}


void Enemy::Rotation()
{
	Vector3 m_forward = m_moveSpeed;
	m_forward.y = 0.0f;
	m_forward.Normalize();
	Quaternion quaternion;
	quaternion.SetRotationY(atan2f(m_forward.x, m_forward.z));
	m_modelRender.SetRotation(quaternion);

}

void Enemy::Render(RenderContext& rc)
{
	m_modelRender.SetRotation(rot);
	m_modelRender.Draw(rc);
}


