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
	SetScale({ 1,1,1 });
	SetRotation({ 0,-90,0 });
	SetPosition({ 0,-6,0 });
	SetRadius({ radius,radius });
	//�R���C�_�[�̒ǉ�
	//���a���������畂���Ă�����W�����S
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	//���ʂ�ݒ肷��
	SetIdentification(IDENT_PLAYER);
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
	//�d��
	Gravity();
	//�ړ�
	Move();
	//�A�C�e���ɑ΂���s��
	Retention();

	if (position.y <= -50)
	{
		position = { 0,0,0 };
		SetEye({ 0,0,-50 });
		SetTarget({ 0,0,0 });
	}

	Object3d::Update();
}

void Player::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_PLANE) 
	{
		//�����ȃI�u�W�F�N�g�ɓ���������
		if (info.object->GetIdentification() == IDENT_NEUTRAL)
		{
			yadd = 0.0f;
			isJamp = false;

			//���n�ɓ������Ă��Ă߂荞��ł�����
			if (position.y < -13.0f)
			{
				//���n�̏�ɍ��킹��
				position.y = -13.0f;
			}
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
			if (input->TriggerKey(DIK_Z) && !isRetention)
			{
				//�ێ��t���O��^�ɂ���
				isRetention = true;
			}
			if (isStop)
			{
				isJamp = false;
				yadd = 0.0f;
			}
		}
		//�G���I�u�W�F�N�gor�G�ɓ���������
		if (info.object->GetIdentification() == IDENT_ENEMY)
		{

		}
		//�p�C�v�ɓ���������
		if (info.object->GetIdentification() == IDENT_PIPE)
		{
			yadd = 0.0f;
			isJamp = false;
			Clim();
		}
	}

	if (info.collider->GetShapeType() == COLISIONSHAPE_BOX)
	{
		//�����ȃI�u�W�F�N�g�ɓ���������
		if (info.object->GetIdentification() == IDENT_NEUTRAL)
		{

		}
		//�G���I�u�W�F�N�gor�G�ɓ���������
		if (info.object->GetIdentification() == IDENT_ENEMY)
		{

		}
		//�A�C�e���ɓ���������
		if (info.object->GetIdentification() == IDENT_ITEM)
		{

		}
		//�ړ��p�Q�[�g�ɓ���������
		if (info.object->GetIdentification() == IDENT_GATE)
		{


		}
		//���ɓ���������
		if (info.object->GetIdentification() == IDENT_FLOOR)
		{
			yadd = 0.0f;
			isJamp = false;
		}
		//�ǂɓ���������
		if (info.object->GetIdentification() == IDENT_WALL)
		{
			if (position.x > info.object->GetPosition().x + info.object->GetRadius().x)
			{
				position.x -= (moveSpeed - radius);
			}
			if (position.x < info.object->GetPosition().x - info.object->GetRadius().x)
			{
				position.x -= (moveSpeed + radius);
			}
		}
	}
}

void Player::Move()
{
	if (input->PushKey(DIK_LEFT))
	{
		if (isMove)
		{
			moveSpeed = -0.4f;
		}
		else
		{
			moveSpeed = 0.0f;
		}
		isDirection = true;

		if (posture == Posture::Croching)
		{
			moveSpeed = -0.2f;
		}

		if (rotation.y != -90)
		{
			rotation.y -= 30;
		}
	}
	else if (input->PushKey(DIK_RIGHT))
	{
		if (isMove)
		{
			moveSpeed = 0.4f;
		}
		else
		{
			moveSpeed = 0.0f;
		}
		isDirection = false;

		if (posture == Posture::Croching)
		{
			moveSpeed = 0.2f;
		}

		if (rotation.y != 90)
		{
			rotation.y += 30;
		}
	}
	else
	{
		moveSpeed = 0.0f;
	}

	//�J�����̈ړ�
	if (position.x > -5.0f && position.x < 280.0f)
	{

		CameraMoveVector({ moveSpeed,0,0 });
	}
	else
	{
		CameraMoveVector({ 0,0,0 });
	}

	position.x += moveSpeed;
}

void Player::Jump()
{
	if (!isJamp && input->TriggerKey(DIK_SPACE))
	{
		yadd = antiYadd;
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
		SetScale({ 1,0.5f,1 });
		position.y -= 0.5f;
		posture = Posture::Croching;
	}
	if (posture == Posture::Croching && input->TriggerKey(DIK_UP))
	{
		moveSpeed = 0.4f;
		SetScale({ 1,1,1 });
		position.y += 0.5f;
		posture = Posture::Upright;
	}
}

void Player::Clim()
{
	if (input->PushKey(DIK_UP))
	{
		position.y += 0.05f;
	}
}

void Player::Gravity()
{
	position.y -= yadd;
	if (yadd <= 1.0f)
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