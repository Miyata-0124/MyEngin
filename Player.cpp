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
	SetSize({ 1,1,1 });
	SetPosition({ 0,0,0, });
	//�R���C�_�[�̒ǉ�
	//���a���������畂���Ă�����W�����S
	SetCollider(new SphereCollider(Vector3{ 0,radius,0 }, radius));
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
		Jump();
		break;
	case Posture::Croching://���Ⴊ��
		//�n�C�W�����v
		HiJump();
		break;
	}
	//�ړ�
	Move();
	//�A�C�e���ɑ΂���s��
	Retention();
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
	else if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{
		//�A�C�e���ɓ���������
		if (input->TriggerKey(DIK_Z) && !isRetention)
		{
			//�ێ��t���O��^�ɂ���
			isRetention = true;
		}
	}
}

void Player::Move()
{
	if (input->PushKey(DIK_LEFT))
	{
		position.x -= moveSpeed;
		isDirection = true;
	}
	else if (input->PushKey(DIK_RIGHT))
	{
		position.x += moveSpeed;
		isDirection = false;
	}
}

void Player::Jump()
{
	if (!isJamp && input->TriggerKey(DIK_SPACE))
	{
		yadd -= 1.5f;
		isJamp = true;
	}
}

void Player::HiJump()
{

}

void Player::ChangePosture()
{
	if (posture == Posture::Upright &&input->TriggerKey(DIK_DOWN))
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

void Player::Retention()
{
	//����ێ����Ă���
	if (isRetention)
	{
		//X�L�[�������ꂽ��
		if (input->TriggerKey(DIK_X))
		{
			isRetention = false;
		}
	}
}
