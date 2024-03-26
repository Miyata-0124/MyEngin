#include "header/Game/APBox.h"
#include "header/Collider/BoxCollider.h"

APBox* APBox::Create(Model* model)
{
	//インスタンス生成
	APBox* instance = new APBox();
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

bool APBox::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//初期座標指定
	SetScale({ 1,1,1 });
	SetRotation({ 0,0,0 });
	SetPosition({ 0,0,0 });
	SetRadius({ 2.0f,2.0f });
	//コライダーの追加
	//半径分足元から浮いている座標が中心
	SetCollider(new BoxCollider(XMVECTOR({ 0,GetRadius().y,0,0}), GetRadius()));
	//識別を設定する
	SetIdentification(IDENT_ITEM);

	return true;
}

void APBox::Update()
{
    Object3d::Update();
}

void APBox::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{
		//プレイヤーがオブジェクトに当たった時
		if (info.object->GetIdentification() == IDENT_PLAYER)
		{
			//箱を空けるアニメーションを追加する
		}
	}
}
