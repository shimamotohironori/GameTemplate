#include "stdafx.h"
#include "Player.h"
#include "collision/CollisionObject.h"
#include<random>

bool Player::Start()
{
    //アニメーションクリップをロードする。
    animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");    //待機
    animationClips[enAnimationClip_Idle].SetLoopFlag(true);
    animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");    //歩く
    animationClips[enAnimationClip_Walk].SetLoopFlag(true);
    animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");    //ジャンプ
    animationClips[enAnimationClip_Jump].SetLoopFlag(false);
    animationClips[enAnimationClip_PushLever].Load("Assets/animData/push_lever.tka");   //レバーを押す
    animationClips[enAnimationClip_PushLever].SetLoopFlag(false);
    animationClips[enAnimationClip_run].Load("Assets/animData/run.tka");     //走る
    animationClips[enAnimationClip_run].SetLoopFlag(true);

    m_spriteRender.Init("Assets/sprite/player.dds", 512.0f, 128.0f);
    //m_spriteRender.Update();
    m_spriteRender.SetPosition({ -500.0f,300.0f,0.0f });
   //m_spriteRender.SetScale();
    m_spriteRender.SetPivot({ 0.0f,0.5f });

    //ユニティちゃん。
    modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);
    //modelRender.Init("Assets/modelData/enemy.tkm");
    position.x = 15000.0f;
    position.y = 12.0f;
    position.z = -2.0f;
    m_charaCon.Init(25.0f, 50.0f, position);
    //modelRender.SetPosition(position);

    //ユニティちゃんの進行方向
    rot.SetRotationDegY(-90.0f);

    //position.y = 512.0f;
    modelRender.SetPosition(position);
    modelRender.Update();

    m_collisionObject = NewGO<CollisionObject>(0);
    m_collisionObject->CreateCapsule(
        m_position,
        Quaternion::Identity,
        25.0f, 50.0f
    );
    m_collisionObject->SetName("player");
    m_collisionObject->SetIsEnableAutoDelete(false);

    m_collisionObject->SetPosition(position + Vector3(0.0f,0.0f,100.0f));
    return true;
}

void Player::Update()
{
    //ステート管理。
    ManageState();

    //アニメーションの再生。
    PlayAnimation();

    //回転処理。
    Rotation();

    //コリジョン予定

    //座標の表示。
    debugpositiony();

    ProcessCommonStateTransition();

    //移動処理
    Move();

    if (SP >= 100.0f)
    {
        SP = 100.0f;
    }
    if (SP <= 0.0f)
    {
        SP = 0.0f;
    }

    if (SP == 0.0f)
    {
        cooltime = true;
    }
    else if (SP >= 50)
    {
        cooltime = false;
    }
    SPBer = SP / 100.0f;

    m_spriteRender.SetScale({ SPBer,1.0f,0.0f });
    m_spriteRender.Update();

  

    const auto& collisions = g_collisionObjectManager->FindCollisionObjects("TOGE");
    //コリジョンの配列をfor文で回す。
    for (auto collision : collisions)
    {

        //コリジョンとキャラコンが衝突したら。
        if (collision->IsHit(m_collisionObject))
        {
            togeCount = 1;
            return;
        }

        if (m_collisionObject->IsHit(collision))
        {
            togeCount = 1;
            return;
        }

        if (m_collisionObject->IsHit(m_charaCon))
        {
            togeCount = 1;
            //return;
    }
        if (collision->IsHit(m_charaCon))
        {
            togeCount = 1;
        }
    }


    //絵描きさんの更新処理。
    //debugpositiony();
    modelRender.Update();
}

//ユニティちゃんの動き
void Player::Move()
{
    //xzの移動速度を0.0fにする。
    moveSpeed.x = 0.0f;
    moveSpeed.z = 0.0f;

    //左スティックの入力量を取得。
    Vector3 stickL;
    stickL.x = g_pad[0]->GetLStickXF();
    stickL.y = g_pad[0]->GetLStickYF();



    //カメラの前方向と右方向のベクトルを持ってくる。
    Vector3 forward = g_camera3D->GetForward();
    Vector3 right = g_camera3D->GetRight();

    //y方向には移動させない。
    forward.y = 0.0f;
    right.y = 0.0f;


    if (g_pad[0]->IsPress(enButtonRB1) && SP > 0  && cooltime == false)
    {
        moveSpeed += forward * stickL.y * 1500.0f;
        moveSpeed += right * stickL.x * 1500.0f;
     //   right *= stickL.x * 1500.0f;//移動速度
     //   forward *= stickL.y * 1500.0f;
        if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
        {
            SP--;
        }
        else {
            SP++;
        }
    }
    else {
        SP++;
        //左スティックの入力量と120.0fを乗算。
        moveSpeed += forward * stickL.y *300.0f;
        moveSpeed += right * stickL.x * 300.0f;
     //   right *= stickL.x * 300.0f;        //移動速度
     //   forward *= stickL.y * 300.0f;
    }
    //移動速度に上記で計算したベクトルを加算する。
  //  moveSpeed += right + forward;

    if (m_charaCon.IsOnGround())
    {
        moveSpeed.y = 0.0f;
        if (g_pad[0]->IsTrigger(enButtonA))
        {
            moveSpeed.y = 500.0f;//ジャンプ力
        }

    }

    else
    {
        /*if (g_pad[0]->IsPress(enButtonLB1))
        {

            if (moveSpeed.y <= -50.0f)
            {
                moveSpeed.y += 10.0f;
            }
            else
            {
                moveSpeed.y -= 50.0f;
            }
        }*/
        GravitySpeed();
    }
    //キャラクターコントローラーを使って座標を移動させる。

    position = m_charaCon.Execute(moveSpeed, 1.0f / 60.0f);

    //絵描きさんに座標を教える。
    modelRender.SetPosition(position);
    
}

//ユニティちゃん回転。
void Player::Rotation()
{
    //xかzの移動速度があったら(スティックの入力があったら)。
    if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
    {
        //キャラクターの方向を変える。
        rot.SetRotationYFromDirectionXZ(moveSpeed);
        //絵描きさんに回転を教える。
        modelRender.SetRotation(rot);
    }

    //プレイヤーの正面ベクトルを計算する。
    m_forward = Vector3::AxisZ;
    rot.Apply(m_forward);
}

//レバーを押します
void Player::MakePushLeverCollision()
{
    //コリジョンオブジェクトを作成する。
    auto collisionObject = NewGO<CollisionObject>(0);
    Vector3 collisionPosition = position;
    //座標をプレイヤーの少し前に設定する。
    collisionPosition += m_forward * 50.0f;
    //球状のコリジョンを作成する。
    collisionObject->CreateSphere(collisionPosition, Quaternion::Identity, 70.0f);
    collisionObject->SetName("player_lever");
}

//重力
void Player::GravitySpeed()
{
    moveSpeed.y -= 7.5f;
}

//ステート管理。
void Player::ManageState()
{
    //地面に付いていなかったら。
    if (m_charaCon.IsOnGround() == false)
    {
        //ステートを1(ジャンプ中)にする。
        playerState = 1;

        //ここでManageState関数の処理を終わらせる。
        return;
    }

    //地面に付いていたら。
    //xかzの移動速度があったら(スティックの入力があったら)。
    if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
    {
        //ステート2(歩き)にする。
        playerState = 2;

        if (g_pad[0]->IsPress(enButtonRB1) && cooltime == false)
        {
            playerState = 3;
        }
    }

    //xとzの移動速度が無かったら(スティックの入力が無かったら)。
    else
    {
        //ステートを0(待機)にする。
        playerState = 0;
    }
}

void Player::ProcessCommonStateTransition()
{
    //Xボタンが押されたら。
    if (g_pad[0]->IsTrigger(enButtonX))
    {
    //レバーを押すステートに移行する。
    m_playerState = enPlayerState_PushLever;
    //レバーを押すためのコリジョンを作成する。
    MakePushLeverCollision();
    return;
    }
}

void Player::ProcessPushLeverStateTransition()
{
    //レバーを押すアニメーションの再生が終わったら。
    if (modelRender.IsPlayingAnimation() == false)
    {
        //ステートを遷移する。
        ProcessCommonStateTransition();
    }
}

//アニメーションの再生。
void Player::PlayAnimation()
{
    //switch文。
    switch (playerState) {
        //プレイヤーステートが0(待機)だったら。
    case 0:
        //待機アニメーションを再生する。
        modelRender.PlayAnimation(enAnimationClip_Idle);
        break;
        //プレイヤーステートが1(ジャンプ中)だったら。
    case 1:
        //ジャンプアニメーションを再生する。
        modelRender.PlayAnimation(enAnimationClip_Jump);
        break;
        //プレイヤーステートが2(歩き)だったら。
    case 2:
        //歩きアニメーションを再生する。
        modelRender.PlayAnimation(enAnimationClip_Walk);
        break;
    case 3:
        //走るアニメーションを再生する。
        modelRender.PlayAnimation(enAnimationClip_run);
        break;
    case 4:
        //レバーを押すアニメーションを再生する。
        modelRender.PlayAnimation(enAnimationClip_PushLever,0.1f);
        break;
    }
}

void Player::debugpositiony()
{
    int x = position.x;
    wchar_t wcsbuf[256];
    swprintf_s(wcsbuf, 256, L"X:%d", x);

    //表示するテキストを設定。
    fontRender.SetText(wcsbuf);
    //フォントの位置を設定。
    fontRender.SetPosition(Vector3(200.0f, 200.0f, 0.0f));
    //フォントの大きさを設定。
    fontRender.SetScale(2.0f);

    int y = position.y;
    wchar_t wcsbuf2[256];
    swprintf_s(wcsbuf2, 256, L"Y:%d", y);

    //表示するテキストを設定。
    fontRender2.SetText(wcsbuf2);
    //フォントの位置を設定。
    fontRender2.SetPosition(Vector3(200.0f, 0.0f, 0.0f));
    //フォントの大きさを設定。
    fontRender2.SetScale(2.0f);

    int z = position.z;
    wchar_t wcsbuf3[256];
    swprintf_s(wcsbuf3, 256, L"Z:%d", z);

    //表示するテキストを設定。
    fontRender3.SetText(wcsbuf3);
    //フォントの位置を設定。
    fontRender3.SetPosition(Vector3(200.0f, -200.0f, 0.0f));
    //フォントの大きさを設定。
    fontRender3.SetScale(2.0f);
}

void Player::Render(RenderContext& rc)
{
    modelRender.SetRotation(rot);
    modelRender.Draw(rc);
    m_spriteRender.Draw(rc);
    fontRender.Draw(rc);
    fontRender2.Draw(rc);
    fontRender3.Draw(rc);
}