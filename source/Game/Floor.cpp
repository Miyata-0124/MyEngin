#include "header/Game/Floor.h"
#include "header/Collider/PlaneCollider.h"

Floor* Floor::Create(Model* model)
{
	//インスタンス生成
	Floor* instance = new Floor();
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

bool Floor::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	SetScale({ 60,1,60, });
	SetRotation({ 0,0,0 });
	SetPosition({ 0, -15, 0 });
	SetRadius({ radius.x,radius.y });
	//コライダーの追加
	SetDistance({ position.x, position.y + radius.y+radius.y, position.z });
	//中心座標と原点からの距離
	SetCollider(new PlaneCollider(XMVECTOR({ 0,position.y + radius.y,0,0 }), distance.m128_f32[1]));
	//識別を設定する
	SetIdentification(IDENT_NEUTRAL);
	return true;
}

void Floor::Update()
{
	Object3d::Update();
}

void Floor::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{

	}
}
