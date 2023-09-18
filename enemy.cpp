#include "enemy.h"
#include "SphereCollider.h"

using namespace DirectX;

Enemy* Enemy::Create(Model* model)
{
	//インスタンス生成
	Enemy* instance = new Enemy();
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

bool Enemy::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//初期座標指定
	SetSize({ 1,1,1 });
	SetPosition({ 0,0,0, });
	//コライダーの追加
	//半径分足元から浮いている座標が中心
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	return true;
}

void Enemy::Update()
{
	switch (posture)
	{
	case EnemyPosture::Wait:
		if (position.x > 0)
		{
			position.x -= 0.1f;
		}
		else if (position.x < 0)
		{
			position.x += 0.1f;
		}
		else
		{

		}
		break;
	case EnemyPosture::Move:
		if (position.x >= 10)
		{
			speed = -speed;
		}
		else if (position.x <= -10)
		{
			speed = -speed;
		}

		position.x += speed;
		break;
	default:
		break;
	}

	if (ChengeTimer >= 0)
	{
		ChengeTimer--;
	}
	else
	{
		if (posture == EnemyPosture::Wait)
		{
			posture = EnemyPosture::Move;
		}
		else if(posture==EnemyPosture::Move)
		{
			posture = EnemyPosture::Wait;
		}
		ChengeTimer = 50;
	}
	Object3d::Update();
}

void Enemy::OnCollider(const CollisionInfo& info)
{
}
