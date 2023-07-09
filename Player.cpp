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
	//�p�[�e�B�N���𔭐�������
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
