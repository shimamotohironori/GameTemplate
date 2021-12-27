#pragma once

//�h�A//

class Door : public IGameObject
{
public:
	//�h�A�X�e�[�g�B
	enum EnDoorState {
		enDoorState_Idle,				//�ҋ@�B
		enDoorState_Open,				//�I�[�v���B
		enDoorState_Open_Idle,			//�I�[�v�����I������B
		enDoorState_Close,				//�N���[�Y�B
		enDoorState_Close_Idle			//�N���[�Y���I������B
	};
public:
	Door();
	~Door();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void NotifyOpen(); //�����J��
	void NotifyClose();//�����܂�

	//�h�A�̍��W
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	//�h�A�̉�]
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	//�h�A�̑傫��
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	//�h�A�̔ԍ�
	void SetDoorNumber(const int doorNumber)
	{
		m_doorNumber = doorNumber;
	}

	//�h�A�̔ԍ����擾����
	const int GetDoorNumber() const
	{
		return m_doorNumber;
	}
private:
	void PlayAnimation();               //�A�j���[�V�����̍Đ�
	void ReleasePhysicsObject();        //�t�B�W�b�N�X�I�u�W�F�N�g�̓����蔻����J������
	void CreatePhysicsObject();         //�t�B�W�b�N�X�I�u�W�F�N�g�̓����蔻����쐬����
	void ManageState();                 //�X�e�[�g�Ǘ��B
	void ProcessOpenStateTransition();  //�I�[�v���X�e�[�g�̃X�e�[�g�J�ڏ���
	void ProcessCloseStateTransition(); //�N���[�Y�X�e�[�g�̃X�e�[�g�J�ڏ���
private:
	ModelRender m_modelRender;
	Vector3 m_position;
	Quaternion m_rotation;
	Vector3 m_scale = Vector3::One;
	enum EnAnimationClip {           //�A�j���[�V����
		enAnimationClip_Idle,        //�ҋ@
		enAnimationClip_Open,        //�J��
		enAnimationClip_Close,       //����
		enAnimationClip_Num,         //�A�j���[�V�����̐�
	};
	AnimationClip       m_animationClips[enAnimationClip_Num];   //�A�j���[�V�����N���b�v
	PhysicsStaticObject m_physicsStaticObject;                    //�t�B�W�N�X�X�^�e�B�b�N�I�u�W�F�N�g
	EnDoorState         m_doorState = enDoorState_Idle;          //�h�A�̃X�e�[�g
	int                 m_doorNumber = 0;                        //�h�A�̔ԍ�     
};

