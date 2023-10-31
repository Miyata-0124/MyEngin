#include "header/Game/enemy.h"
#include "header/Collider/SphereCollider.h"

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
	SetPosition({ 15,0,0 });
	//�R���C�_�[�̒ǉ�
	//���a���������畂���Ă�����W�����S
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	//���ʂ�ݒ肷��
	SetIdentification(IDENT_ENEMY);
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
		if (position.x > 10.5f)
		{
			position.x -= 0.1f;
		}
		else if (position.x < 9.5f)
		{
			position.x += 0.1f;
		}
		else
		{

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

	//�d�͉��Z
	Gravity();
	Object3d::Update();
}

void Enemy::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_PLANE)
	{
		//�����ȃI�u�W�F�N�g�ɓ���������
		if (info.object->GetIdentification() == IDENT_NEUTRAL)
		{

		}
		//�A�C�e���ɓ���������
		if (info.object->GetIdentification() == IDENT_ITEM)
		{

		}
		//�G���I�u�W�F�N�gor�G�ɓ���������
		if (info.object->GetIdentification() == IDENT_ENEMY)
		{

		}
	}
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{
		//�����ȃI�u�W�F�N�g�ɓ���������
		if (info.object->GetIdentification() == IDENT_NEUTRAL)
		{

		}
		//�A�C�e���ɓ���������
		if (info.object->GetIdentification() == IDENT_ITEM)
		{

		}
		//�G���I�u�W�F�N�gor�G�ɓ���������
		if (info.object->GetIdentification() == IDENT_ENEMY)
		{

		}
	}
	if (info.collider->GetShapeType() == COLISIONSHAPE_BOX)
	{
		//�����ȃI�u�W�F�N�g�ɓ���������
		if (info.object->GetIdentification() == IDENT_NEUTRAL)
		{
			yadd = 0.0f;
		}
		//�A�C�e���ɓ���������
		if (info.object->GetIdentification() == IDENT_ITEM)
		{

		}
		//�G���I�u�W�F�N�gor�G�ɓ���������
		if (info.object->GetIdentification() == IDENT_ENEMY)
		{

		}
		
	}
}

void Enemy::Gravity()
{
	position.y -= yadd;
	yadd += 0.2f;
}
