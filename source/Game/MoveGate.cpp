#include "header/Game/MoveGate.h"
#include "header/Collider/BoxCollider.h"

MoveGate* MoveGate::Create(Model* model)
{
	//インスタンス生成
	MoveGate* instance = new MoveGate();
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

bool MoveGate::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//初期座標指定
	SetScale({ 1,1,1 });
	SetRotation({ 0,0,0 });
	SetPosition({ 30,-7,0 });
	SetRadius({ radius.x,radius.y });
	//コライダーの追加
	//半径分足元から浮いている座標が中心
	SetCollider(new BoxCollider(XMVECTOR({ 0,radius.y,0,0 }), radius));
	//識別を設定する
	SetIdentification(IDENT_GATE);
	return true;
}

void MoveGate::Update()
{
	Object3d::Update();
}

void MoveGate::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{
		if (info.object->GetIdentification() == IDENT_PLAYER)
		{
			if (input->TriggerKey(DIK_V))
			{
				isMapMove = true;
			}
		}
	}
}
