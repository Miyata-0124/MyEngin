#include "Player.h"
#include "SphereCollider.h"

using namespace DirectX;

Player* Player::Create(Model* model)
{
	//�C���X�^���X����
	Player* instance = new Player();
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

bool Player::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//�������W�w��
	SetPosition({ -10,0,0, });
	//�R���C�_�[�̒ǉ�
	//���a���������畂���Ă�����W�����S
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	return true;
}

void Player::Update()
{
	//�ړ�
	Move();
	//�W�����v
	Jamp();
	//�d��
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
