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
		speed = 0.0f;
		break;
	case EnemyPosture::Move:
		/*if (playerPosition.x > position.x)
		{
			speed = 0.2f;
		}
		else if (playerPosition.x < position.x)
		{
			speed = -0.2f;
		}
		position.x += speed;*/
		break;
	default:
		break;
	}

	if (ChengeTimer > 0)
	{
		ChengeTimer--;
	}
	else
	{
		if (posture == EnemyPosture::Wait)
		{
			ChengeTimer = 100;
			posture = EnemyPosture::Move;
		}
		else
		{
			ChengeTimer = 50;
			posture = EnemyPosture::Wait;
		}
	}

	Gravity();
	Object3d::Update();
}

void Enemy::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_PLANE)
	{
		yadd = 0.0f;
	}
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{
		/*if (playerPosition.x > position.x)
		{
			move = - 0.5f;
		}
		else if (playerPosition.x < position.x)
		{
			move = 0.5f;
		}
		else
		{
			move = 0;
		}
		position.x += move;*/
	}
}

void Enemy::Gravity()
{
	position.y -= yadd;
	yadd += 0.2f;
}
