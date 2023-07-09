#include "Player.h"
#include "Input.h"
#include "SphereCollider.h"

using namespace DirectX;

Player* Player::Create(Model* model)
{
	//インスタンス生成
	Player* instance = new Player();
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

bool Player::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//コライダーの追加
	float radius = 0.6f;
	//半径分足元から浮いている座標が中心
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	return true;
}

void Player::Update()
{
	position.y -= yadd;
	yadd += 0.2f;
	if (position.y <= -5.0f)
	{
		yadd = 0.0f;
	}
	Object3d::Update();
}

void Player::OnCollider(const CollisionInfo& info)
{
	//パーティクルを発生させる
}
