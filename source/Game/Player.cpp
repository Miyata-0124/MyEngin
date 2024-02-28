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
	SetPosition({ -64,0,0 });
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
	//ジャンプ
	Jump();
	//重力
	Gravity();
	//移動
	Move();
	//アイテムに対する行動
	Retention();
	//行動制限
	//スクロール
	if (position.x > -65 && position.x < 115)
	{
		SetEye({ position.x,0,-50 });
		SetTarget({ position.x,0,0 });

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
		}
		//敵性オブジェクトor敵に当たった時
		if (info.object->GetIdentification() == IDENT_ENEMY)
		{

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
			//Y軸
			//床のX,Y最大値を取得
			float floorMAXY = info.object->GetPosition().y + info.object->GetRadius().y;
			//float floorMAXX = info.object->GetPosition().x + info.object->GetRadius().x;
			//最小値を取得
			//float floorMINY = info.object->GetPosition().y - info.object->GetRadius().y;
			//float floorMINX = info.object->GetPosition().x - info.object->GetRadius().x;
			//0.1触れるようにする
			float adj = 0.1f;
			//自分の座標が床の最大よりも下(床にめり込んでいるなら)
			if (position.y < floorMAXY && position.y > floorMAXY - 1.0f)
			{
				//床に0.1触れさせるように戻す
				position.y = floorMAXY - adj;
				yadd = 0.0f;
				isJamp = false;
			}
		}
		//壁に当たった時
		if (info.object->GetIdentification() == IDENT_WALL)
		{
			//Y軸
			//床のX,Yの最大値を取得
			float floorMAXY = info.object->GetPosition().y + info.object->GetRadius().y;
			//float floorMAXX = info.object->GetPosition().x + info.object->GetRadius().x;
			//最小値を取得
			//float floorMINY = info.object->GetPosition().y - info.object->GetRadius().y;
			//float floorMINX = info.object->GetPosition().x - info.object->GetRadius().x;
			//0.1触れるようにする
 			float adj = 0.1f;
			//上に乗っているかどうかの判定
			if (position.y - radius < floorMAXY && position.y - radius > floorMAXY - 0.5f)
			{
				//床に0.1触れさせるように戻す
				position.y = floorMAXY - adj;
				yadd = 0.0f;
				isJamp = false;
			}


		}
		//パイプに当たった時
		if (info.object->GetIdentification() == IDENT_PIPE)
		{
			yadd = 0.0f;
			isJamp = false;
			Clim();
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