#include "header/Game/Pipe.h"
#include "header/Collider/SphereCollider.h"

Pipe* Pipe::Create(Model* model)
{
	//インスタンス生成
	Pipe* instance = new Pipe();
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

bool Pipe::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//初期座標指定
	SetScale({ 1,1,1 });
	SetRotation({ 0,90,0 });
	SetPosition({ 0,0,0, });
	SetRadius({ 3.0f,3.0f });
	//コライダーの追加
	//半径分足元から浮いている座標が中心
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius.y,0,0 }), radius.y));
	//識別を設定する
	SetIdentification(IDENT_PIPE);
	return true;
}

void Pipe::Update()
{
	Object3d::Update();
}

void Pipe::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{

	}
}
