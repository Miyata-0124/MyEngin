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
	SetScale({ 1,1,1});
	SetRotation({ 0,90,0 });
	SetPosition({ 0,0,0, });
	SetRadius({ 5.0f,5.0f });
	//コライダーの追加
	//半径分足元から浮いている座標が中心
	SetCollider(new BoxCollider(XMVECTOR({ 0,GetRadius().y,0,0}), GetRadius()));
	//識別を設定する
	SetIdentification(IDENT_FLOOR);
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
