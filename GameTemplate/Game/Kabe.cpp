#include "stdafx.h"
#include "Kabe.h"
#include "Game.h"

bool Kabe::Start()
{
	//��
	m_modelRender.Init("Assets/modelData/stage/kabe.tkm");
	//���W
/*	m_position.x = -6410.0f;
	m_position.y = 5.0f;
	m_position.z = -14793.0f;
*/
//���W
	m_modelRender.SetPosition(m_position);
	//�傫��
	m_modelRender.SetScale(m_scale);
	//��]��ݒ肷��B
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
	//���f����`�悷��B
	m_modelRender.Draw(rc);
}