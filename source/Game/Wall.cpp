#include "header/Game/Wall.h"
#include "header/Collider/BoxCollider.h"

using namespace DirectX;

Wall* Wall::Create(Model* model)
{
	//インスタンス生成
	Wall* instance = new Wall();
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

bool Wall::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//初期座標指定
	SetSize({ 1.0f,3.0f,1.0f });
	SetPosition({ 0,-12,0, });
	//コライダーの追加
	//半径分足元から浮いている座標が中心
	SetCollider(new BoxCollider(XMVECTOR({ 0,radius.y,0,0 }), radius));
	//識別を設定する
	SetIdentification(IDENT_GATE);
	return true;
}

void Wall::Update()
{
	Object3d::Update();
}

void Wall::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{

	}
}
