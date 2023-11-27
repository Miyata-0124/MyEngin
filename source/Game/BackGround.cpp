#include "header/Game/BackGround.h"

BackGround* BackGround::Create(Model* model)
{
	//インスタンス生成
	BackGround* instance = new BackGround();
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

bool BackGround::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//初期座標指定
	SetScale({ 60,60,60 });
	SetRotation({ 0,90,0 });
	SetPosition({ 0,0,0, });
	return true;
}

void BackGround::Update()
{
	Object3d::Update();
}
