#include "Player.h"
#include "Input.h"
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
	//�R���C�_�[�̒ǉ�
	float radius = 0.6f;
	//���a���������畂���Ă�����W�����S
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	return true;
}

void Player::Update()
{
	position.y -= yadd;
	yadd += 0.2f;
	if (position.y <= -5.0f)
	{
		yadd = 0.0f;
	}
	Object3d::Update();
}

void Player::OnCollider(const CollisionInfo& info)
{
	//�p�[�e�B�N���𔭐�������
}
