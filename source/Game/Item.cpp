#include "header/Game/Item.h"
#include "header/Collider/SphereCollider.h"

Item* Item::Create(Model* model)
{
	//インスタンス生成
	Item* instance = new Item();
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

bool Item::Initialize()
{

	if (!Object3d::Initialize())
	{
		return false;
	}
	//初期座標指定
	SetSize({ 0.5f,0.5f,0.5f });
	SetPosition({ -15,-13,0, });
	//コライダーの追加
	//半径分足元から浮いている座標が中心
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	//識別を設定する
	SetIdentification(IDENT_ITEM);
	return true;
}

void Item::Update()
{
	//保持投擲の挙動
	RetentionThrow();
	//重力
	Gravity();
	Object3d::Update();
}

void Item::OnCollider(const CollisionInfo& info)
{
	//床に当たったなら
	if (info.collider->GetShapeType() == COLISIONSHAPE_PLANE)
	{
		//中立なオブジェクトに当たった時
		if (info.object->GetIdentification() == IDENT_NEUTRAL)
		{
			yadd = 0.0f;
			isThrow = false;
		}
		//アイテムに当たった時
		if (info.object->GetIdentification() == IDENT_ITEM)
		{

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
			yadd = 0.0f;
			isThrow = false;
		}
		//アイテムに当たった時
		if (info.object->GetIdentification() == IDENT_ITEM)
		{

		}
		//敵性オブジェクトor敵に当たった時
		if (info.object->GetIdentification() == IDENT_ENEMY)
		{

		}
		if (info.object->GetIdentification() == IDENT_PLAYER)
		{
			yadd = 0.0f;
			isThrow = false;
		}
	}
	if (info.collider->GetShapeType() == COLISIONSHAPE_BOX)
	{
		//中立なオブジェクトに当たった時
		if (info.object->GetIdentification() == IDENT_NEUTRAL)
		{
			yadd = 0.0f;
			isThrow = false;
		}
		//アイテムに当たった時
		if (info.object->GetIdentification() == IDENT_ITEM)
		{

		}
		//敵性オブジェクトor敵に当たった時
		if (info.object->GetIdentification() == IDENT_ENEMY)
		{

		}
	}
}

void Item::RetentionThrow()
{
	if (isRetention)
	{
		SetPosition({ playerPosition.x,playerPosition.y,playerPosition.z });
		if (input->TriggerKey(DIK_X))
		{
			if (!isThrow && !input->PushKey(DIK_DOWN))
			{
				ThrowLength();
				isThrow = true;
			}
			if (input->PushKey(DIK_DOWN))
			{
				isRetention = false;
			}
		}
	}
	//投擲された
	if (isThrow)
	{
		position.y += (float)height;
		position.x += (float)length;
	}

}

void Item::Gravity()
{
	if (isRetention == false)
	{
		position.y -= yadd;
		yadd += 0.2f;
	}
}

void Item::ThrowLength()
{
	//左向き
	if (isDirection)
	{
		//最高到達点
		height = (throwSpeed * sin(30)) * (throwSpeed * sin(30)) / 2 * g;
		//最高到達距離
		length = (throwSpeed * throwSpeed) * sin(30) * 2 / g;
	}
	//右向き
	else
	{//最高到達点
		height = (throwSpeed * sin(30)) * (throwSpeed * sin(30)) / 2 * g;
		//最高到達距離
		length = -((throwSpeed * throwSpeed) * sin(30) * 2 / g);

	}
}