#include "header/Game/Player.h"
#include "header/Collider/SphereCollider.h"

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
	SetPosition({ -20,0,0 });
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
		Jump();
		break;
	case Posture::Croching://���Ⴊ��
		//�n�C�W�����v
		//HiJump();
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
		//SetPosition({ position.x,-13,0 });
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
	else if (info.collider->GetShapeType() == COLISIONSHAPE_BOX)
	{
		yadd = 0.0f;
		isJamp = false;
		if (input->PushKey(DIK_UP))
		{
			position.y +=0.03f;
		}
	}
}

void Player::Move()
{
	if (input->PushKey(DIK_LEFT))
	{
		if (position.x > -42)
		{
			moveSpeed = -0.4f;
		}
		else
		{
			moveSpeed = 0.0f;
		}
		
		isDirection = true;
	}
	else if (input->PushKey(DIK_RIGHT))
	{
		if (position.x < 42)
		{
			moveSpeed = 0.4f;
		}
		else
		{
			moveSpeed = 0.0f;
		}
		isDirection = false;
	}
	else
	{
		moveSpeed = 0.0f;
	}

	position.x += moveSpeed;
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
	if (yadd <= 2.0f)
	{
		yadd += 0.2f;
	}
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