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
	//移動
	Move();
	//ジャンプ
	Jamp();
	//重力
	Gravity();
	Object3d::Update();
}

void Player::OnCollider(const CollisionInfo& info)
{
	yadd = 0.0f;
}

void Player::Move()
{
	if (input->PushKey(DIK_LEFT))
	{
		position.x -= 0.5f;
	}
	else if (input->PushKey(DIK_RIGHT))
	{
		position.x += 0.5f;
	}
}

void Player::Jamp()
{
	if (input->TriggerKey(DIK_SPACE))
	{
		yadd -= 1.5f;
	}
}

void Player::Gravity()
{
	position.y -= yadd;
	yadd += 0.2f;
}
