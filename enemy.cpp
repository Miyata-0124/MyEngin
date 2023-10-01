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
		posture = EnemyPosture::Serch;
		break;
	case EnemyPosture::Serch:
		if (position.x > 0.5f)
		{
			position.x -= 0.1f;
		}
		else if (position.x < -0.5f)
		{
			position.x += 0.1f;
		}


		if (playerPosition.x < position.x + (radius * 10) && playerPosition.x > position.x - (radius * 10))
		{
			if (playerPosition.y < position.y + (radius * 10) && playerPosition.y > position.y - (radius * 10))
			{
				posture = EnemyPosture::Move;
			}
		}
		break;
	case EnemyPosture::Move:
		if (playerPosition.x < position.x + (radius * 10) && playerPosition.x > position.x - (radius * 10))
		{
			if (playerPosition.y < position.y + (radius * 10) && playerPosition.y > position.y - (radius * 10))
			{
				if (playerPosition.x > position.x)
				{
					speed = 0.2f;
				}
				else if (playerPosition.x < position.x)
				{
					speed = -0.2f;
				}
			}
		}
		else
		{
			posture = EnemyPosture::Serch;
		}
		position.x += speed;
		break;
	default:
		break;
	}

	//重力加算
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
