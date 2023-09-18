#include "enemy.h"
#include "SphereCollider.h"

using namespace DirectX;

Enemy* Enemy::Create(Model* model)
{
	//�C���X�^���X����
	Enemy* instance = new Enemy();
	if (instance == nullptr)
	{
		return nullptr;
	}
	//������
	if (!instance->Initialize()) {
		delete instance;
		assert(0);
	}
	//���f���Z�b�g
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
	//�������W�w��
	SetSize({ 1,1,1 });
	SetPosition({ 0,0,0, });
	//�R���C�_�[�̒ǉ�
	//���a���������畂���Ă�����W�����S
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
