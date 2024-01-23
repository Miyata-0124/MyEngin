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
	if (position.x > -5.0f && position.x < 867.0f)
	{
		if (position.y > -220.0f && position.y < 100.0f)
		{
			SetEye({ position.x,position.y,-50 });
			SetTarget({ position.x,position.y,0 });
		}
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
			//床の最大値を取得
			float floorMAX = info.object->GetPosition().y + info.object->GetRadius().y;
			//最小値を取得
			//float floorMIN = info.object->GetPosition().y - info.object->GetRadius().y;
			//最大値に0.1触れるようにする
			float adj = 0.1f;
			//自分の座標が床の最大よりも下(床にめり込んでいるなら)
			if (position.y - radius < floorMAX)
			{
				//床に0.1触れさせるように戻す
				position.y = floorMAX - adj;
				yadd = 0.0f;
				isJamp = false;
			}
		}
		//壁に当たった時
		if (info.object->GetIdentification() == IDENT_WALL)
		{
			if (position.x > info.object->GetPosition().x + info.object->GetRadius().x)
			{
				
			}
			if (position.x < info.object->GetPosition().x - info.object->GetRadius().x)
			{

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

	position.x += moveSpeed;
}

void Player::Jump()
{
	if (!isJamp && input->TriggerKey(DIK_SPACE))
	{
		//重力をマイナスにして飛ばす
		yadd = antiYadd;
		//飛んでると伝える
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
	float climeSpeed = 0.0f;
	if (input->PushKey(DIK_UP))
	{
		climeSpeed = 0.5f;
		position.y += climeSpeed;
		
	}

	if (input->PushKey(DIK_DOWN))
	{
		climeSpeed = -0.5f;
		position.y += climeSpeed;
	}
}

void Player::Gravity()
{
	//重力を加算する
	position.y -= yadd;
	//ジャンプされたとき
	if (yadd <= 1.0f)
	{
		//加算する値を大きくしていく
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