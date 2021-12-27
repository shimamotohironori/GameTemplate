#include "stdafx.h"
#include "Lever.h"
#include "Door.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "collision/CollisionObject.h"

Lever::Lever()
{
	
}

Lever::~Lever()
{
	//�R���W�����I�u�W�F�N�g���폜����B
	DeleteGO(m_collisionObject);
}

bool Lever::Start()
{
	//�A�j���[�V������ǂݍ��ށB
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/lever/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Push].Load("Assets/animData/lever/push.tka");
	m_animationClips[enAnimationClip_Push].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Pull].Load("Assets/animData/lever/pull.tka");
	m_animationClips[enAnimationClip_Pull].SetLoopFlag(false);
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/lever/lever.tkm", m_animationClips, enAnimationClip_Num);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);

	//�R���W�����I�u�W�F�N�g���쐬�B
	m_collisionObject = NewGO<CollisionObject>(0);
	//�{�b�N�X��̃R���W�������쐬�B
	m_collisionObject->CreateBox(m_position, m_rotation, Vector3(70.0f,70.0f,70.0f));
	m_collisionObject->SetName("lever");
	m_collisionObject->SetIsEnableAutoDelete(false);

	//����ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/lever.wav");
	return true;
}

void Lever::Update()
{
	//�A�j���[�V�������Đ�����B
	PlayAnimation();
	//�X�e�[�g�Ǘ��B
	ManageState();

	//���f���̍X�V�B
	m_modelRender.Update();
}

void Lever::ProcessTransitionPushState()
{
	//�v���C���[���쐬�����A���o�[�p�̃R���W�����̔z����擾�B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_lever");

	//for���Ŕz����񂷁B
	for (auto collision : collisions)
	{
		//���o�[���g�̃R���W�����ƃv���C���[�̍쐬�����R���W�������Փ˂�����B
		if (collision->IsHit(m_collisionObject) == true)
		{
			//�����X�e�[�g�ɑJ�ڂ�����B
			m_leverState = enLeverState_Push;
			break;
		}
	}
}

void Lever::ProcessTransitionPullState()
{
//�v���C���[���쐬�����A���o�[�p�̃R���W�����̔z����擾�B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_lever");

	//for���Ŕz����񂷁B
	for (auto collision : collisions)
	{
		//���o�[���g�̃R���W�����ƃv���C���[�̍쐬�����R���W�������Փ˂�����B
		if (collision->IsHit(m_collisionObject) == true)
		{
			//�����X�e�[�g�ɑJ�ڂ���B
			m_leverState = enLeverState_Pull;
			break;
		}
	}
}

void Lever::PlayAnimation()
{
	switch (m_leverState)
	{
		//�ҋ@�X�e�[�g�Ȃ�B
	case enLeverState_Idle:
		//�ҋ@�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
		//�����X�e�[�g�̎��B
	case enLeverState_Push:
		//�����A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Push);
		break;
		//�����X�e�[�g�̂Ƃ��B
	case enLeverState_Pull:
		//�����A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Pull);
		break;
	default:
		break;
	}
}

void Lever::ProcessTransitionPushIdleState()
{
	//�����A�j���[�V�����̍Đ����I�������B
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//�h�A�̃I�u�W�F�N�g�̔z����擾����B
		auto doors = FindGOs<Door>("door");
		//for���Ŕz����񂷁B
		for (auto door : doors)
		{
			//���o�[�̔ԍ��ƃh�A�̔ԍ�����v���Ă�����B
			if (m_leverNumber == door->GetDoorNumber())
			{
				//�h�A�ɊJ���邱�Ƃ�ʒm����B
				door->NotifyOpen();
				m_leverState = enLeverState_Push_Idle;
				break;
			}
		}
	}
}

void Lever::ProcessTransitionPullIdleState()
{
	//�����A�j���[�V�����̍Đ����I�������B
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//�h�A�̃I�u�W�F�N�g�̔z����擾����B
		auto doors = FindGOs<Door>("door");
		//for���Ŕz����񂷁B
		for (auto door : doors)
		{
			//���o�[�̔ԍ��ƃh�A�̔ԍ�����v���Ă�����B
			if (m_leverNumber == door->GetDoorNumber())
			{
				//�h�A�ɕ߂邱�Ƃ�ʒm����B
				door->NotifyClose();
				m_leverState = enLeverState_Pull_Idle;
				break;
			}
		}
	}
}

void Lever::ProcessIdleStateTransition()
{
	//�ҋ@��Ԃ��牟����Ԃւ̑J�ځB
	ProcessTransitionPushState();
}

void Lever::ProcessPushStateTransition()
{
	//������Ԃ���ҋ@��Ԃւ̑J�ځB
	ProcessTransitionPushIdleState();
}

void Lever::ProcessPushIdleStateTransition()
{
	//�ҋ@��Ԃ��������Ԃւ̑J�ځB
	ProcessTransitionPullState();
}

void Lever::ProcessPullStateTransition()
{
	//������Ԃ���ҋ@��Ԃւ̑J�ځB
	ProcessTransitionPullIdleState();
}

void Lever::ProcessPullIdleStateTransition()
{
	//�ҋ@��Ԃ��牟����Ԃւ̑J�ځB
	ProcessTransitionPushState();
}

void Lever::ManageState()
{
	switch (m_leverState)
	{
		//�ҋ@�X�e�[�g�̎��B
	case enLeverState_Idle:
		//�ҋ@�X�e�[�g�̃X�e�[�g�J�ڏ����B
		ProcessIdleStateTransition();
		break;
		//�����X�e�[�g�̎��B
	case enLeverState_Push:
		//�����X�e�[�g�̃X�e�[�g�J�ڏ����B
		ProcessPushStateTransition();
		break;
		//�����I������X�e�[�g�̎��B
	case enLeverState_Push_Idle:
		//�����I������X�e�[�g�̃X�e�[�g�J�ڏ����B
		ProcessPushIdleStateTransition();
		break;
		//�����X�e�[�g�̎��B
	case enLeverState_Pull:
		//�����X�e�[�g�̃X�e�[�g�J�ڏ����B
		ProcessPullStateTransition();
		break;
		//�����I������X�e�[�g�̎��B
	case enLeverState_Pull_Idle:
		//�����I������X�e�[�g�̃X�e�[�g�J�ڏ����B
		ProcessPullIdleStateTransition();
		break;
	default:
		break;
	}
}

void Lever::Render(RenderContext& rc)
{
	//���f����`�悷��B
	m_modelRender.Draw(rc);
}