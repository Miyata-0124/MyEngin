#include "Floor.h"
#include "PlaneCollider.h"

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
	//コライダーの追加
	float distance = 0.0f;
	//半径分足元から浮いている座標が中心
	SetCollider(new PlaneCollider(XMVECTOR({ 0,1,0,0 }), distance));
	return true;
}

void Floor::Update()
{
	Object3d::Update();
}

void Floor::OnCollider(const CollisionInfo& info)
{

}
