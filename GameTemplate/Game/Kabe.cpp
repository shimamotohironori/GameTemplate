#include "stdafx.h"
#include "Kabe.h"
#include "Game.h"

bool Kabe::Start()
{
	//壁
	m_modelRender.Init("Assets/modelData/stage/kabe.tkm");
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

	return true;
}

Kabe::~Kabe()
{

}

void Kabe::Update()
{
	m_modelRender.Update();
}

void Kabe::Render(RenderContext& rc)
{
	//モデルを描画する。
	m_modelRender.Draw(rc);
}