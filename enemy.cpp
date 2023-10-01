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
