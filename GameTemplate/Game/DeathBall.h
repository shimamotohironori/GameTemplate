#pragma once
#include "sound/SoundSource.h"
class Player;
class Enemy;
class DeathBall:public IGameObject
{
public:
	bool Start()override;
	void Render(RenderContext& rc)override;
	void Update()override;

	//モデルレンダ―。        
	ModelRender m_modelRender;
	SphereCollider m_sphereCollider;//円型のコライダー。
	RigidBody m_rigidBody;
	//Vector3 m_position;  //座標。
	Vector3 position; //座標
	Vector3 diff = Vector3::One * 100.0f;
	Player* player;//プレイヤー
	Enemy* enemy;//エネミー
	Vector3 Position; //初期座標
	//ゴーストオブジェクト。
	//PhysicsGhostObject m_physicsGhostObject;
	SoundSource* se;
	FontRender m_fontRender; //文字
	float m_get = 0.0f;
};

