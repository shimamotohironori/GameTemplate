#pragma once

//���o�[//
//class CollisionObject;
class Lever : public IGameObject
{
public:
	//���o�[�X�e�[�g
	enum EnLeverState {
		enLeverState_Idle,				//�ŏ��̑ҋ@��ԁB
		enLeverState_Push,				//�����B
		enLeverState_Push_Idle,			//�����I������B
		enLeverState_Pull,				//�����B
		enLeverState_Pull_Idle			//�����I������B
	};
public:
	Lever();
	~Lever();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//���W��ݒ肷��
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	//��]��ݒ肷��
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	//�傫����ݒ肷��
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	//���o�[�̔ԍ���ݒ肷��
	void SetLeverNumber(const int leverNumber)
	{
		m_leverNumber = leverNumber;
	}
	//���o�[�̔ԍ����擾����
	const int  GetLeverNumber() const
	{
		return m_leverNumber;
	}
private:
	//�����X�e�[�g�Ɉڍs���鏈��
	void ProcessTransitionPushState();
	//�����I������X�e�[�g�Ɉڍs���鏈��
	void ProcessTransitionPushIdleState();
	//�����X�e�[�g�Ɉڍs���鏈��
	void ProcessTransitionPullState();
	//�����I������X�e�[�g�Ɉڍs���鏈��
	void ProcessTransitionPullIdleState();
	//�A�j���[�V�������Đ����鏈��
	void PlayAnimation();
	//�X�e�[�g�Ǘ�
	void ManageState();
	//�ҋ@��Ԃ̃X�e�[�g�J�ڏ����B
	void ProcessIdleStateTransition();
	// �����X�e�[�g�̑J�ڏ����B
	void ProcessPushStateTransition();
	// �����I������X�e�[�g�̑J�ڏ����B
	void ProcessPushIdleStateTransition();
	//�����X�e�[�g�̑J�ڏ����B
	void ProcessPullStateTransition();
	//�����I������X�e�[�g�̑J�ڏ����B
	void ProcessPullIdleStateTransition();

	enum EnAnimationClip {          //�A�j���[�V����
		enAnimationClip_Idle,       //�ҋ@
		enAnimationClip_Push,       //����
		enAnimationClip_Pull,       //����
		enAnimationClip_Num,        //�A�j���[�V�����̐�
	};
	AnimationClip   m_animationClips[enAnimationClip_Num];
	ModelRender     m_modelRender;
	Vector3         m_position;
	Vector3         m_scale = Vector3::One;
	Quaternion      m_rotation;
	CollisionObject* m_collisionObject;              //�R���W�����I�u�W�F�N�g�B
	EnLeverState    m_leverState = enLeverState_Idle;
	int             m_leverNumber = 0;
};

