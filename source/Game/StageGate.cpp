#include "header/Game/StageGate.h"
#include "header/Collider/BoxCollider.h"

StageGate* StageGate::Create(Model* model)
{
	//インスタンス生成
	StageGate* instance = new StageGate();
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

bool StageGate::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//初期座標指定
	SetSize({ 2,2,2 });
	SetRotation({ 0,0,0 });
	SetPosition({ 40,-13,0 });
	//コライダーの追加
	//半径分足元から浮いている座標が中心
	SetCollider(new BoxCollider(XMVECTOR({ 0,radius.y,0,0 }), radius));
	//識別を設定する
	SetIdentification(IDENT_GATE);
	return true;
}

void StageGate::Update()
{
	Object3d::Update();
}

void StageGate::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{

	}
}
