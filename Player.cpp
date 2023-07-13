#include "Player.h"
#include "SphereCollider.h"

using namespace DirectX;

Player* Player::Create(Model* model)
{
	//インスタンス生成
	Player* instance = new Player();
	if (instance == nullptr)
	{
		return nullptr;
	}
	//初期化
	if (!instance->Initialize()) {
		delete instance;
		assert(0);
	}
	//モデルセット
	if (model) {
		instance->SetModel(model);
	}
	return instance;
}

bool Player::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//初期座標指定
	SetPosition({ -10,0,0, });
	//コライダーの追加
	//半径分足元から浮いている座標が中心
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	return true;
}

void Player::Update()
{
	//姿勢変更情報
	ChangePosture();
	switch (posture)
	{
	case Posture::Upright://直立
		//ジャンプ
		Jamp();
		break;
	case Posture::Croching://しゃがみ
		break;
	}
	//移動
	Move();
	//重力
	Gravity();
	Object3d::Update();
}

void Player::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_PLANE)
	{
		yadd = 0.0f;
		isJamp = false;
	}
}

void Player::Move()
{
	if (input->PushKey(DIK_LEFT))
	{
		position.x -= moveSpeed;
	}
	else if (input->PushKey(DIK_RIGHT))
	{
		position.x += moveSpeed;
	}
}

void Player::Jamp()
{
	if (!isJamp && input->TriggerKey(DIK_SPACE))
	{
		yadd -= 1.5f;
		isJamp = true;
	}
}

void Player::ChangePosture()
{
	if (posture == Posture::Upright && input->TriggerKey(DIK_DOWN))
	{
		moveSpeed = 0.3f;
		SetSize({ 1,0.5f,1 });
		position.y -= 0.5f;
		posture = Posture::Croching;
	}
	if (posture == Posture::Croching && input->TriggerKey(DIK_UP))
	{
		moveSpeed = 0.4f;
		SetSize({ 1,1,1 });
		position.y += 0.5f;
		posture = Posture::Upright;
	}
}

void Player::Gravity()
{
	position.y -= yadd;
	yadd += 0.2f;
}
