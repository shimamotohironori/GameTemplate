#pragma once
class Eenmy;
class DeathBall;
class Goal;
class Collision;
class Lever;
class Toge;
class Trap;

class Player:public IGameObject
{
public:
    Player() {}; //�R���X�g���N�^
    ~Player() {}; //�f�X�g���N�^

    bool Start();  //����������
    void Update();  //�X�V����
    void Move();  //�v���C���[�̓���
    void Rotation();  //��]�̏���
    void Render(RenderContext& rc);  //�`�揈���B
    void GravitySpeed();  //�d�͂̃X�s�[�h
    void debugpositiony();//y���W��\������
    void PlayAnimation(); //�A�j���[�V����
    void ManageState(); //�v���C���[�̏�ԊǗ�

    enum EnPlayerState {
        enPlayerState_PushLever,			//���o�[�������B
    };

    enum EnAnimationClip {		//�A�j���[�V�����B
        enAnimationClip_Idle,
        enAnimationClip_Walk,       //����
        enAnimationClip_Jump,       //�W�����v
        enAnimationClip_run,        //����
        enAnimationClip_PushLever,  //���o�[�������B
        enAnimationClip_Num,
    };
    AnimationClip animationClips[enAnimationClip_Num];		//�A�j���[�V�����N���b�v�B
    ModelRender modelRender;  //���f���̕`��
    const Vector3& GetPosition() const//���W�̎擾
    {
        return position;
    }
    // ���o�[���������́A�����蔻��p�̃R���W�������쐬����B
    void MakePushLeverCollision();
    //���o�[�������X�e�[�g�̑J�ڏ����B
    void ProcessPushLeverStateTransition();
    //���ʂ̃X�e�[�g�J�ڏ����B
    void ProcessCommonStateTransition();


    CharacterController m_charaCon;  //�L�����N�^�[�R���g���[���[
    Quaternion rot;        //��]�B
    FontRender fontRender;  //�����̕`��
    FontRender fontRender2;  //�����̕`��
    FontRender fontRender3;  //�����̕`��
    //bool m_isHit = false ;
    Vector3	m_forward = Vector3::AxisZ;		//�v���C���[�̐��ʃx�N�g���B
    Vector3 m_position;  //�f�X�{�[���̍��W�B
    Vector3 position;            //���W�B
    Vector3 moveSpeed;        //�ړ����x�B
    EnPlayerState m_playerState = enPlayerState_PushLever;
    DeathBall*deathBall;    //�f�X�{�[���B
    Eenmy* enemy;        //�G�l�~�[�B
    Goal* goal;   //�S�[��
    Toge* toge;
    Trap* trap;
    SpriteRender m_spriteRender;
    //�S�[�X�g�I�u�W�F�N�g�B
    //PhysicsGhostObject m_physicsGhostObject;
    int deathBallCount = 0;
    int enemyCount = 0;
    int goalCount = 0;
    int togeCount = 0;
    int trapCount = 0;
    int fallspeed = 0;            //�v���C���[�̗����X�s�[�h
    int playerState = 0;        //�v���C���[�̏��
    float SP = 100.0f;    //�X�^�~�i
    float SPBer = 100.0f;    //�X�^�~�i�o�[
    bool cooltime= false;
    CollisionObject* m_collisionObject = nullptr;
};

