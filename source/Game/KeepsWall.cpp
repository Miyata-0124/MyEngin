#include "header/Game/KeepsWall.h"
#include "header/Collider/BoxCollider.h"

KeepsWall* KeepsWall::Create(Model* model)
{
	//インスタンス生成
	KeepsWall* instance = new KeepsWall();
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

bool KeepsWall::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//初期座標指定
	SetScale({ 1,1,1 });
	SetRotation({ 0,0,0 });
	SetPosition({ 0,0,0, });
	SetRadius({ 10,20 });
	//コライダーの追加
	//半径分足元から浮いている座標が中心
	SetCollider(new BoxCollider(XMVECTOR({ 0,GetRadius().y,0,0}), GetRadius()));
	//識別を設定する
	SetIdentification(IDENT_WALL);
	return true;
}

void KeepsWall::Update()
{
	Object3d::Update();
}

void KeepsWall::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{

	}
}
