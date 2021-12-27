#include "stdafx.h"
#include "DeathBall.h"
#include "Player.h"
#include "Enemy.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
//#include <random>

bool DeathBall::Start()
{
	//デスボールの状態。
	m_modelRender.Init("Assets/modelData/stage/DeathBall.tkm");
	//m_modelRender.Init("Assets/modelData/stage/DieBall.tkm");
	m_modelRender.SetScale({ 2.0f,2.0f, 2.0f });
	/*//乱数を生成
	constexpr int MIN = -790;//乱数の範囲最低値
	constexpr int MAX = 790;//乱数の範囲最大値
	constexpr int RAND_NUMS_TO_GENERATE = 2;//乱数を生成する回数*/

	//デスボールの乱数。
	/*std::random_device rd;
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
	//m_position.y = 2600.0f;
	//m_position.y = 100.0f;
	//m_position.z = 12.0f;
	m_modelRender.SetPosition(Position);
	m_modelRender.Update();


	//コライダーを初期化。
	m_sphereCollider.Create(55.0f);

	//剛体を初期化。
	RigidBodyInitData rbInitData;
	//質量(重さ)を設定する。
	rbInitData.mass = 10.0f;
	//コライダーを設定する。
	rbInitData.collider = &m_sphereCollider;
	//座標を設定する。
	rbInitData.pos = Position;
	//回転のしやすさを設定する。0～1
	rbInitData.localInteria.Set(
		0.5f,
		0.5f,
		0.5f
	);
	//反発力を設定する。
	//数値を大きくすると、跳ね返りが大きくなる。
	//PhysicsStaticObjectにも反発力を設定する必要がある(Game.cpp参照)。
	rbInitData.restitution = 1.0f;
	//剛体を初期化。
	m_rigidBody.Init(rbInitData);
	//摩擦力を設定する。0～10まで。
	m_rigidBody.SetFriction(0.0f);
	//線形移動する要素を設定する。
	//0を指定した軸は移動しない。
	//例えばyを0に指定すると、y座標は移動しなくなる。
	m_rigidBody.SetLinearFactor(1.0f, 1.0f, 1.0f);

	player = FindGO<Player>("player");  //プレイヤーを見つける。

	enemy = FindGO<Enemy>("enemy");     //エネミーを見つける。

	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/boll.wav");  //効果音
		
	//ゴーストオブジェクトを初期化。
	//Quaternion rot;
	//m_physicsGhostObject.CreateSphere(m_position,rot, 20.0f);
	Vector3 force = { 900.0f,00.0f,900.0f };
	m_rigidBody.AddForce(
		force,		//力
		g_vec3Zero	//力を加える剛体の相対位置
	);
	return true;
}



void DeathBall::Update()
{

	Vector3 pos;
	Vector3 enemy;
	Quaternion rot;
	//剛体の座標と回転を取得。
	m_rigidBody.GetPositionAndRotation(pos, rot);
	//剛体の座標と回転をモデルに反映。
	m_modelRender.SetPosition(pos);
	m_modelRender.SetRotation(rot);
	//剛体に力を加える。
	Vector3 force = { 0.0f,-5000.0f,0.0f };
	m_rigidBody.AddForce(
		force,		//力
		g_vec3Zero	//力を加える剛体の相対位置
	);

	Vector3 vector = player->position;
	vector.y += 30.0f;
	//プレイヤーからデスボールに向かうベクトルを計算。
	diff = vector - pos;
	//ベクトルの長さが120.0fより小さかったら。
	if (diff.Length() <= 120.0f)
	{
		player->deathBallCount += 1;
		//自身を削除する。
		//DeleteGO(this);
	}



	//モデルの更新処理。
	m_modelRender.Update();

}



void DeathBall::Render(RenderContext& rc)
{
	//モデルを描画する。
	m_modelRender.Draw(rc);
	m_fontRender.Draw(rc);
}