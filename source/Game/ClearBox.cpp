#include "header/Game/ClearBox.h"
#include "header/Collider/BoxCollider.h"

ClearBox* ClearBox::Create(Model* model)
{

	//インスタンス生成
	ClearBox* instance = new ClearBox();
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

bool ClearBox::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	SetScale({ 1,1,1, });
	SetPosition({ 15, -13.0f, 0 });
	//コライダーの追加
	//中心座標と原点からの距離
	SetCollider(new BoxCollider(XMVECTOR({ 0,radius.y,0,0 }), radius));
	//識別を設定する
	SetIdentification(IDENT_GOAL);

	isGoal = false;

	return true;
}

void ClearBox::Update()
{
	Object3d::Update();
}

void ClearBox::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{
		//中立なオブジェクトに当たった時
		if (info.object->GetIdentification() == IDENT_NEUTRAL)
		{
		
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
 			isGoal = true;
		}
	}
}
