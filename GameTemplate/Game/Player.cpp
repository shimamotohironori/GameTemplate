#include "stdafx.h"
#include "Player.h"
#include "collision/CollisionObject.h"
#include<random>

bool Player::Start()
{
    //�A�j���[�V�����N���b�v�����[�h����B
    animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");    //�ҋ@
    animationClips[enAnimationClip_Idle].SetLoopFlag(true);
    animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");    //����
    animationClips[enAnimationClip_Walk].SetLoopFlag(true);
    animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");    //�W�����v
    animationClips[enAnimationClip_Jump].SetLoopFlag(false);
    animationClips[enAnimationClip_PushLever].Load("Assets/animData/push_lever.tka");   //���o�[������
    animationClips[enAnimationClip_PushLever].SetLoopFlag(false);
    animationClips[enAnimationClip_run].Load("Assets/animData/run.tka");     //����
    animationClips[enAnimationClip_run].SetLoopFlag(true);

    m_spriteRender.Init("Assets/sprite/player.dds", 512.0f, 128.0f);
    //m_spriteRender.Update();
    m_spriteRender.SetPosition({ -500.0f,300.0f,0.0f });
   //m_spriteRender.SetScale();
    m_spriteRender.SetPivot({ 0.0f,0.5f });

    //���j�e�B�����B
    modelRender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);
    //modelRender.Init("Assets/modelData/enemy.tkm");
    position.x = 15000.0f;
    position.y = 12.0f;
    position.z = -2.0f;
    m_charaCon.Init(25.0f, 50.0f, position);
    //modelRender.SetPosition(position);

    //���j�e�B�����̐i�s����
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
    //�X�e�[�g�Ǘ��B
    ManageState();

    //�A�j���[�V�����̍Đ��B
    PlayAnimation();

    //��]�����B
    Rotation();

    //�R���W�����\��

    //���W�̕\���B
    debugpositiony();

    ProcessCommonStateTransition();

    //�ړ�����
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
    //�R���W�����̔z���for���ŉ񂷁B
    for (auto collision : collisions)
    {

        //�R���W�����ƃL�����R�����Փ˂�����B
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


    //�G�`������̍X�V�����B
    //debugpositiony();
    modelRender.Update();
}

//���j�e�B�����̓���
void Player::Move()
{
    //xz�̈ړ����x��0.0f�ɂ���B
    moveSpeed.x = 0.0f;
    moveSpeed.z = 0.0f;

    //���X�e�B�b�N�̓��͗ʂ��擾�B
    Vector3 stickL;
    stickL.x = g_pad[0]->GetLStickXF();
    stickL.y = g_pad[0]->GetLStickYF();



    //�J�����̑O�����ƉE�����̃x�N�g���������Ă���B
    Vector3 forward = g_camera3D->GetForward();
    Vector3 right = g_camera3D->GetRight();

    //y�����ɂ͈ړ������Ȃ��B
    forward.y = 0.0f;
    right.y = 0.0f;


    if (g_pad[0]->IsPress(enButtonRB1) && SP > 0  && cooltime == false)
    {
        moveSpeed += forward * stickL.y * 1500.0f;
        moveSpeed += right * stickL.x * 1500.0f;
     //   right *= stickL.x * 1500.0f;//�ړ����x
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
        //���X�e�B�b�N�̓��͗ʂ�120.0f����Z�B
        moveSpeed += forward * stickL.y *300.0f;
        moveSpeed += right * stickL.x * 300.0f;
     //   right *= stickL.x * 300.0f;        //�ړ����x
     //   forward *= stickL.y * 300.0f;
    }
    //�ړ����x�ɏ�L�Ōv�Z�����x�N�g�������Z����B
  //  moveSpeed += right + forward;

    if (m_charaCon.IsOnGround())
    {
        moveSpeed.y = 0.0f;
        if (g_pad[0]->IsTrigger(enButtonA))
        {
            moveSpeed.y = 500.0f;//�W�����v��
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
    //�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B

    position = m_charaCon.Execute(moveSpeed, 1.0f / 60.0f);

    //�G�`������ɍ��W��������B
    modelRender.SetPosition(position);
    
}

//���j�e�B������]�B
void Player::Rotation()
{
    //x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
    if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
    {
        //�L�����N�^�[�̕�����ς���B
        rot.SetRotationYFromDirectionXZ(moveSpeed);
        //�G�`������ɉ�]��������B
        modelRender.SetRotation(rot);
    }

    //�v���C���[�̐��ʃx�N�g�����v�Z����B
    m_forward = Vector3::AxisZ;
    rot.Apply(m_forward);
}

//���o�[�������܂�
void Player::MakePushLeverCollision()
{
    //�R���W�����I�u�W�F�N�g���쐬����B
    auto collisionObject = NewGO<CollisionObject>(0);
    Vector3 collisionPosition = position;
    //���W���v���C���[�̏����O�ɐݒ肷��B
    collisionPosition += m_forward * 50.0f;
    //����̃R���W�������쐬����B
    collisionObject->CreateSphere(collisionPosition, Quaternion::Identity, 70.0f);
    collisionObject->SetName("player_lever");
}

//�d��
void Player::GravitySpeed()
{
    moveSpeed.y -= 7.5f;
}

//�X�e�[�g�Ǘ��B
void Player::ManageState()
{
    //�n�ʂɕt���Ă��Ȃ�������B
    if (m_charaCon.IsOnGround() == false)
    {
        //�X�e�[�g��1(�W�����v��)�ɂ���B
        playerState = 1;

        //������ManageState�֐��̏������I��点��B
        return;
    }

    //�n�ʂɕt���Ă�����B
    //x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
    if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
    {
        //�X�e�[�g2(����)�ɂ���B
        playerState = 2;

        if (g_pad[0]->IsPress(enButtonRB1) && cooltime == false)
        {
            playerState = 3;
        }
    }

    //x��z�̈ړ����x������������(�X�e�B�b�N�̓��͂�����������)�B
    else
    {
        //�X�e�[�g��0(�ҋ@)�ɂ���B
        playerState = 0;
    }
}

void Player::ProcessCommonStateTransition()
{
    //X�{�^���������ꂽ��B
    if (g_pad[0]->IsTrigger(enButtonX))
    {
    //���o�[�������X�e�[�g�Ɉڍs����B
    m_playerState = enPlayerState_PushLever;
    //���o�[���������߂̃R���W�������쐬����B
    MakePushLeverCollision();
    return;
    }
}

void Player::ProcessPushLeverStateTransition()
{
    //���o�[�������A�j���[�V�����̍Đ����I�������B
    if (modelRender.IsPlayingAnimation() == false)
    {
        //�X�e�[�g��J�ڂ���B
        ProcessCommonStateTransition();
    }
}

//�A�j���[�V�����̍Đ��B
void Player::PlayAnimation()
{
    //switch���B
    switch (playerState) {
        //�v���C���[�X�e�[�g��0(�ҋ@)��������B
    case 0:
        //�ҋ@�A�j���[�V�������Đ�����B
        modelRender.PlayAnimation(enAnimationClip_Idle);
        break;
        //�v���C���[�X�e�[�g��1(�W�����v��)��������B
    case 1:
        //�W�����v�A�j���[�V�������Đ�����B
        modelRender.PlayAnimation(enAnimationClip_Jump);
        break;
        //�v���C���[�X�e�[�g��2(����)��������B
    case 2:
        //�����A�j���[�V�������Đ�����B
        modelRender.PlayAnimation(enAnimationClip_Walk);
        break;
    case 3:
        //����A�j���[�V�������Đ�����B
        modelRender.PlayAnimation(enAnimationClip_run);
        break;
    case 4:
        //���o�[�������A�j���[�V�������Đ�����B
        modelRender.PlayAnimation(enAnimationClip_PushLever,0.1f);
        break;
    }
}

void Player::debugpositiony()
{
    int x = position.x;
    wchar_t wcsbuf[256];
    swprintf_s(wcsbuf, 256, L"X:%d", x);

    //�\������e�L�X�g��ݒ�B
    fontRender.SetText(wcsbuf);
    //�t�H���g�̈ʒu��ݒ�B
    fontRender.SetPosition(Vector3(200.0f, 200.0f, 0.0f));
    //�t�H���g�̑傫����ݒ�B
    fontRender.SetScale(2.0f);

    int y = position.y;
    wchar_t wcsbuf2[256];
    swprintf_s(wcsbuf2, 256, L"Y:%d", y);

    //�\������e�L�X�g��ݒ�B
    fontRender2.SetText(wcsbuf2);
    //�t�H���g�̈ʒu��ݒ�B
    fontRender2.SetPosition(Vector3(200.0f, 0.0f, 0.0f));
    //�t�H���g�̑傫����ݒ�B
    fontRender2.SetScale(2.0f);

    int z = position.z;
    wchar_t wcsbuf3[256];
    swprintf_s(wcsbuf3, 256, L"Z:%d", z);

    //�\������e�L�X�g��ݒ�B
    fontRender3.SetText(wcsbuf3);
    //�t�H���g�̈ʒu��ݒ�B
    fontRender3.SetPosition(Vector3(200.0f, -200.0f, 0.0f));
    //�t�H���g�̑傫����ݒ�B
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