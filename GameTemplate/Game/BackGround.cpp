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
    //PhysicsStaticObjectを初期化。
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
    //モデルの更新処理。
    m_modelRender.Update();
}

//フィジックスオブジェクトの当たり判定の解放
void BackGround::ReleasePhysicsObject()
{
    m_physicsStaticObject.Release();
}
//フィジックスオブジェクトの当たり判定の生成
void BackGround::CreatePhysicsObject()
{
    m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

void BackGround::Render(RenderContext& rc)
{

    //モデルを描画する。

    m_modelRender.Draw(rc);

}