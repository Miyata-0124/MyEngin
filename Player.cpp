#include "Player.h"
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
	//初期座標指定
	SetPosition({ -10,0,0, });
	//コライダーの追加
	//半径分足元から浮いている座標が中心
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	return true;
}

void Player::Update()
{
	if (input->PushKey(DIK_LEFT))
	{
		position.x -= 0.5f;
	}
	else if (input->PushKey(DIK_RIGHT))
	{
		position.x += 0.5f;
	}
	Gravity();
	Object3d::Update();
}

void Player::OnCollider(const CollisionInfo& info)
{
	//パーティクルを発生させる
}

void Player::Gravity()
{
	position.y -= yadd;
	yadd += 0.2f;
	if (position.y <= -5.0f)
	{
		yadd = 0.0f;
	}
}
