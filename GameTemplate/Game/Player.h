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
    Player() {}; //コンストラクタ
    ~Player() {}; //デストラクタ

    bool Start();  //初期化処理
    void Update();  //更新処理
    void Move();  //プレイヤーの動作
    void Rotation();  //回転の処理
    void Render(RenderContext& rc);  //描画処理。
    void GravitySpeed();  //重力のスピード
    void debugpositiony();//y座標を表示する
    void PlayAnimation(); //アニメーション
    void ManageState(); //プレイヤーの状態管理

    enum EnPlayerState {
        enPlayerState_PushLever,			//レバーを押す。
    };

    enum EnAnimationClip {		//アニメーション。
        enAnimationClip_Idle,
        enAnimationClip_Walk,       //歩く
        enAnimationClip_Jump,       //ジャンプ
        enAnimationClip_run,        //走る
        enAnimationClip_PushLever,  //レバーを押す。
        enAnimationClip_Num,
    };
    AnimationClip animationClips[enAnimationClip_Num];		//アニメーションクリップ。
    ModelRender modelRender;  //モデルの描写
    const Vector3& GetPosition() const//座標の取得
    {
        return position;
    }
    // レバーを押す時の、当たり判定用のコリジョンを作成する。
    void MakePushLeverCollision();
    //レバーを押すステートの遷移処理。
    void ProcessPushLeverStateTransition();
    //共通のステート遷移処理。
    void ProcessCommonStateTransition();


    CharacterController m_charaCon;  //キャラクターコントローラー
    Quaternion rot;        //回転。
    FontRender fontRender;  //文字の描写
    FontRender fontRender2;  //文字の描写
    FontRender fontRender3;  //文字の描写
    //bool m_isHit = false ;
    Vector3	m_forward = Vector3::AxisZ;		//プレイヤーの正面ベクトル。
    Vector3 m_position;  //デスボールの座標。
    Vector3 position;            //座標。
    Vector3 moveSpeed;        //移動速度。
    EnPlayerState m_playerState = enPlayerState_PushLever;
    DeathBall*deathBall;    //デスボール。
    Eenmy* enemy;        //エネミー。
    Goal* goal;   //ゴール
    Toge* toge;
    Trap* trap;
    SpriteRender m_spriteRender;
    //ゴーストオブジェクト。
    //PhysicsGhostObject m_physicsGhostObject;
    int deathBallCount = 0;
    int enemyCount = 0;
    int goalCount = 0;
    int togeCount = 0;
    int trapCount = 0;
    int fallspeed = 0;            //プレイヤーの落下スピード
    int playerState = 0;        //プレイヤーの状態
    float SP = 100.0f;    //スタミナ
    float SPBer = 100.0f;    //スタミナバー
    bool cooltime= false;
    CollisionObject* m_collisionObject = nullptr;
};

