#include "header/Game/Player.h"
#include "header/Collider/SphereCollider.h"

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
	SetSize({ 1,1,1 });
	SetPosition({ -20,0,0 });
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
		Jump();
		break;
	case Posture::Croching://しゃがみ
		//ハイジャンプ
		//HiJump();
		break;
	}
	//移動
	Move();
	//アイテムに対する行動
	Retention();
	//重力
	Gravity();
	Object3d::Update();
}

void Player::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_PLANE)
	{
		//SetPosition({ position.x,-13,0 });
		yadd = 0.0f;
		isJamp = false;	
	}
	else if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{
		//アイテムに当たった時
		if (input->TriggerKey(DIK_Z) && !isRetention)
		{
			//保持フラグを真にする
			isRetention = true;
		}
	}
	else if (info.collider->GetShapeType() == COLISIONSHAPE_BOX)
	{
		yadd = 0.0f;
		isJamp = false;
		if (input->PushKey(DIK_UP))
		{
			position.y +=0.03f;
		}
	}
}

void Player::Move()
{
	if (input->PushKey(DIK_LEFT))
	{
		if (position.x > -42)
		{
			moveSpeed = -0.4f;
		}
		else
		{
			moveSpeed = 0.0f;
		}
		
		isDirection = true;
	}
	else if (input->PushKey(DIK_RIGHT))
	{
		if (position.x < 42)
		{
			moveSpeed = 0.4f;
		}
		else
		{
			moveSpeed = 0.0f;
		}
		isDirection = false;
	}
	else
	{
		moveSpeed = 0.0f;
	}

	position.x += moveSpeed;
}

void Player::Jump()
{
	if (!isJamp && input->TriggerKey(DIK_SPACE))
	{
		yadd -= 1.5f;
		isJamp = true;
	}
}

void Player::HiJump()
{

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
	if (yadd <= 2.0f)
	{
		yadd += 0.2f;
	}
}

void Player::Retention()
{
	//物を保持していて
	if (isRetention)
	{
		//Xキーが押されたら
		if (input->TriggerKey(DIK_X))
		{
			isRetention = false;
		}
	}
}