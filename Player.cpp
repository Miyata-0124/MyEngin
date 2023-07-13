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
	//�p���ύX���
	ChangePosture();
	switch (posture)
	{
	case Posture::Upright://����
		//�W�����v
		Jamp();
		break;
	case Posture::Croching://���Ⴊ��
		break;
	}
	//�ړ�
	Move();
	//�d��
	Gravity();
	Object3d::Update();
}

void Player::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_PLANE)
	{
		yadd = 0.0f;
		isJamp = false;
	}
}

void Player::Move()
{
	if (input->PushKey(DIK_LEFT))
	{
		position.x -= moveSpeed;
	}
	else if (input->PushKey(DIK_RIGHT))
	{
		position.x += moveSpeed;
	}
}

void Player::Jamp()
{
	if (!isJamp && input->TriggerKey(DIK_SPACE))
	{
		yadd -= 1.5f;
		isJamp = true;
	}
}

void Player::ChangePosture()
{
	if (posture == Posture::Upright && input->TriggerKey(DIK_DOWN))
	{
		moveSpeed = 0.3f;
		SetSize({ 1,0.5f,1 });
		position.y -= 0.5f;
		posture = Posture::Croching;
	}
	if (posture == Posture::Croching && input->TriggerKey(DIK_UP))
	{
		moveSpeed = 0.4f;
		SetSize({ 1,1,1 });
		position.y += 0.5f;
		posture = Posture::Upright;
	}
}

void Player::Gravity()
{
	position.y -= yadd;
	yadd += 0.2f;
}
