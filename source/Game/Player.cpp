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
	SetScale({ 1,1,1 });
	SetRotation({ 0,-90,0 });
	SetPosition({ 0,-6,0 });
	SetRadius({ radius,radius });
	//コライダーの追加
	//半径分足元から浮いている座標が中心
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	//識別を設定する
	SetIdentification(IDENT_PLAYER);
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
	//重力
	Gravity();
	//移動
	Move();
	//アイテムに対する行動
	Retention();

	if (position.y <= -50)
	{
		position = { 0,0,0 };
		SetEye({ 0,0,-50 });
		SetTarget({ 0,0,0 });
	}

	Object3d::Update();
}

void Player::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_PLANE) 
	{
		//中立なオブジェクトに当たった時
		if (info.object->GetIdentification() == IDENT_NEUTRAL)
		{
			yadd = 0.0f;
			isJamp = false;

			//平地に当たっていてめり込んでいたら
			if (position.y < -13.0f)
			{
				//平地の上に合わせる
				position.y = -13.0f;
			}
		}
		//敵性オブジェクトor敵に当たった時
		if (info.object->GetIdentification() == IDENT_ENEMY)
		{

		}
	}

	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{
		//中立なオブジェクトに当たった時
		if (info.object->GetIdentification() == IDENT_NEUTRAL)
		{

		}
		//アイテムに当たった時
		if (info.object->GetIdentification() == IDENT_ITEM)
		{
			if (input->TriggerKey(DIK_Z) && !isRetention)
			{
				//保持フラグを真にする
				isRetention = true;
			}
			if (isStop)
			{
				isJamp = false;
				yadd = 0.0f;
			}
		}
		//敵性オブジェクトor敵に当たった時
		if (info.object->GetIdentification() == IDENT_ENEMY)
		{

		}
		//パイプに当たった時
		if (info.object->GetIdentification() == IDENT_PIPE)
		{
			yadd = 0.0f;
			isJamp = false;
			Clim();
		}
	}

	if (info.collider->GetShapeType() == COLISIONSHAPE_BOX)
	{
		//中立なオブジェクトに当たった時
		if (info.object->GetIdentification() == IDENT_NEUTRAL)
		{

		}
		//敵性オブジェクトor敵に当たった時
		if (info.object->GetIdentification() == IDENT_ENEMY)
		{

		}
		//アイテムに当たった時
		if (info.object->GetIdentification() == IDENT_ITEM)
		{

		}
		//移動用ゲートに当たった時
		if (info.object->GetIdentification() == IDENT_GATE)
		{


		}
		//床に当たった時
		if (info.object->GetIdentification() == IDENT_FLOOR)
		{
			yadd = 0.0f;
			isJamp = false;
		}
		//壁に当たった時
		if (info.object->GetIdentification() == IDENT_WALL)
		{
			if (position.x > info.object->GetPosition().x + info.object->GetRadius().x)
			{
				position.x -= (moveSpeed - radius);
			}
			if (position.x < info.object->GetPosition().x - info.object->GetRadius().x)
			{
				position.x -= (moveSpeed + radius);
			}
		}
	}
}

void Player::Move()
{
	if (input->PushKey(DIK_LEFT))
	{
		if (isMove)
		{
			moveSpeed = -0.4f;
		}
		else
		{
			moveSpeed = 0.0f;
		}
		isDirection = true;

		if (posture == Posture::Croching)
		{
			moveSpeed = -0.2f;
		}

		if (rotation.y != -90)
		{
			rotation.y -= 30;
		}
	}
	else if (input->PushKey(DIK_RIGHT))
	{
		if (isMove)
		{
			moveSpeed = 0.4f;
		}
		else
		{
			moveSpeed = 0.0f;
		}
		isDirection = false;

		if (posture == Posture::Croching)
		{
			moveSpeed = 0.2f;
		}

		if (rotation.y != 90)
		{
			rotation.y += 30;
		}
	}
	else
	{
		moveSpeed = 0.0f;
	}

	//カメラの移動
	if (position.x > -5.0f && position.x < 280.0f)
	{

		CameraMoveVector({ moveSpeed,0,0 });
	}
	else
	{
		CameraMoveVector({ 0,0,0 });
	}

	position.x += moveSpeed;
}

void Player::Jump()
{
	if (!isJamp && input->TriggerKey(DIK_SPACE))
	{
		yadd = antiYadd;
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
		SetScale({ 1,0.5f,1 });
		position.y -= 0.5f;
		posture = Posture::Croching;
	}
	if (posture == Posture::Croching && input->TriggerKey(DIK_UP))
	{
		moveSpeed = 0.4f;
		SetScale({ 1,1,1 });
		position.y += 0.5f;
		posture = Posture::Upright;
	}
}

void Player::Clim()
{
	if (input->PushKey(DIK_UP))
	{
		position.y += 0.05f;
	}
}

void Player::Gravity()
{
	position.y -= yadd;
	if (yadd <= 1.0f)
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