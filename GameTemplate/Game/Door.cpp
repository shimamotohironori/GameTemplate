#include "stdafx.h"
#include "Door.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Door::Door()
{

}

Door::~Door()
{

}

bool Door::Start()
{
	//�A�j���[�V������ǂݍ��ށB
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/door/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Open].Load("Assets/animData/door/open.tka");
	m_animationClips[enAnimationClip_Open].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Close].Load("Assets/animData/door/close.tka");
	m_animationClips[enAnimationClip_Close].SetLoopFlag(false);
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/door/door.tkm", m_animationClips, enAnimationClip_Num);
	//���W��ݒ肷��B
	m_modelRender.SetPosition(m_position);
	//�傫����ݒ肷��B
	m_modelRender.SetScale(m_scale);
	//��]��ݒ肷��B
	m_modelRender.SetRotation(m_rotation);

	//���f���̍X�V�B
	m_modelRender.Update();
	//�����蔻����쐬����B
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	//����ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/door_cut.wav");

	return true;
}

void Door::Update()
{
	//�A�j���[�V�������Đ�����B
	PlayAnimation();
	//�X�e�[�g�Ǘ��B
	ManageState();

	//���f���̍X�V�B
	m_modelRender.Update();
}

//�h�A���J���܂�
void Door::NotifyOpen()
{
	//�I�[�v���X�e�[�g�ɑJ�ڂ���
	m_doorState = enDoorState_Open;
}


//�h�A�����܂�
void Door::NotifyClose()
{
	//�N���[�Y�X�e�[�g�ɑJ�ڂ���
	m_doorState = enDoorState_Close;
}

//�h�A�̃A�j���[�V����
void Door::PlayAnimation()
{
	switch (m_doorState)
	{
		//�ҋ@�X�e�[�g�̎��B
	case enDoorState_Idle:
		//�ҋ@�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
		//�I�[�v���X�e�[�g�̎��B
	case enDoorState_Open:
		//�I�[�v���A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Open);
		m_modelRender.SetAnimationSpeed(0.6f);
		break;
		//�N���[�Y�X�e�[�g�̎��B
	case enDoorState_Close:
		//�N���[�Y�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Close);
		m_modelRender.SetAnimationSpeed(0.6f);
		break;
	default:
		break;
	}
}


//�t�B�W�b�N�X�I�u�W�F�N�g�̓����蔻��̉��
void Door::ReleasePhysicsObject()
{
	m_physicsStaticObject.Release();
}
//�t�B�W�b�N�X�I�u�W�F�N�g�̓����蔻��̐���
void Door::CreatePhysicsObject()
{
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

//�h�A���J���A�j���[�V����
void Door::ProcessOpenStateTransition()
{
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		ReleasePhysicsObject();
		m_doorState = enDoorState_Open_Idle;
	}
}

//�h�A������A�j���[�V����
void Door::ProcessCloseStateTransition()
{
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		CreatePhysicsObject();
		m_doorState = enDoorState_Close_Idle;
	}
}

//�X�e�[�g�Ǘ�
void Door::ManageState()
{
	switch (m_doorState)
	{
		//�ҋ@�X�e�[�g�̎��B
	case Door::enDoorState_Idle:

		break;
		//�I�[�v���X�e�[�g�̎��B
	case Door::enDoorState_Open:
		//�I�[�v���X�e�[�g�̃X�e�[�g�J�ڏ����B
		ProcessOpenStateTransition();
		break;
		//�I�[�v���I���X�e�[�g�̎��B
	case Door::enDoorState_Open_Idle:

		break;
		//�N���[�Y�X�e�[�g�̎��B
	case Door::enDoorState_Close:
		//�N���[�Y�X�e�[�g�̃X�e�[�g�J�ڏ����B
		ProcessCloseStateTransition();
		break;
		//�N���[�Y�I���X�e�[�g�̎��B
	case Door::enDoorState_Close_Idle:

		break;
	default:
		break;
	}
}

void Door::Render(RenderContext& rc)
{
	//���f����`�悷��
	m_modelRender.Draw(rc);
}