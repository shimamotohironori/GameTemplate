#include "stdafx.h"
#include "BackGround.h"
//#include "Player.h"

BackGround::BackGround()
{

    m_modelRender.Init("Assets/modelData/stage/stage4.tkm");
    //m_modelRender.Init("Assets/modelData/backGround/BackGround.tkm");
   //m_modelRender.SetScale({ 5.0f,6.0f, 9.0f });
   //m_modelRender.SetPosition(m_position);
    m_modelRender.SetPosition({ 100.0f,10.0f,0.0f });
    m_modelRender.SetRotation(m_rotation);
    m_modelRender.SetScale(m_scale);
    m_modelRender.Update();
    //PhysicsStaticObject���������B
    m_physicsStaticObject.CreateFromModel(
        m_modelRender.GetModel(),
        m_modelRender.GetModel().GetWorldMatrix(),
        1.0f);
}

BackGround::~BackGround()
{

}

void BackGround::Update()
{
    //���f���̍X�V�����B
    m_modelRender.Update();
}

//�t�B�W�b�N�X�I�u�W�F�N�g�̓����蔻��̉��
void BackGround::ReleasePhysicsObject()
{
    m_physicsStaticObject.Release();
}
//�t�B�W�b�N�X�I�u�W�F�N�g�̓����蔻��̐���
void BackGround::CreatePhysicsObject()
{
    m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

void BackGround::Render(RenderContext& rc)
{

    //���f����`�悷��B

    m_modelRender.Draw(rc);

}