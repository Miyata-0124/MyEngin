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
	SetPosition({ 5,0,0 });
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
	//�s������
	//�X�N���[��
	SetEye({ position.x,position.y,-50 });
	SetTarget({ position.x,position.y,0 });

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
			//Y��
			//���̍ő�l���擾
			float floorMAXY = info.object->GetPosition().y + info.object->GetRadius().y;
			//�ŏ��l���擾
			float floorMINY = info.object->GetPosition().y - info.object->GetRadius().y;
			//0.1�G���悤�ɂ���
			float adj = 0.1f;
			//�����̍��W�����̍ő������(���ɂ߂荞��ł���Ȃ�)
			if (position.y < floorMAXY)
			{
				//����0.1�G�ꂳ����悤�ɖ߂�
				position.y = floorMAXY - adj;
				yadd = 0.0f;
				isJamp = false;
			}
			//�����̍��W�����̍ŏ��l���������痈���Ȃ�
			if (position.y + radius < floorMINY)
			{
				position.y = floorMINY + adj;
			}
		}
		//�ǂɓ���������
		if (info.object->GetIdentification() == IDENT_WALL)
		{
			//Y��
			//���̍ő�l���擾
			float floorMAXY = info.object->GetPosition().y + info.object->GetRadius().y;
			//�ŏ��l���擾
			//float floorMINY = info.object->GetPosition().y - info.object->GetRadius().y;
			//0.1�G���悤�ɂ���
 			float adj = 0.1f;
			//�����̍��W�����̍ő������(���ɂ߂荞��ł���Ȃ�)
			if (position.y - radius < floorMAXY)
			{
				//����0.1�G�ꂳ����悤�ɖ߂�
				position.y = floorMAXY - adj;
				yadd = 0.0f;
				isJamp = false;
			}
		}
		//�p�C�v�ɓ���������
		if (info.object->GetIdentification() == IDENT_PIPE)
		{
			yadd = 0.0f;
			isJamp = false;
			Clim();
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

	position.x += moveSpeed;
}

void Player::Jump()
{
	if (!isJamp && input->TriggerKey(DIK_SPACE))
	{
		//�d�͂��}�C�i�X�ɂ��Ĕ�΂�
		yadd = antiYadd;
		//���ł�Ɠ`����
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
	float climeSpeed = 0.0f;
	if (input->PushKey(DIK_UP))
	{
		climeSpeed = 0.5f;
		position.y += climeSpeed;
	}

	if (input->PushKey(DIK_DOWN))
	{
		climeSpeed = -0.5f;
		position.y += climeSpeed;
	}
}

void Player::Gravity()
{
	//�d�͂����Z����
	position.y -= yadd;
	//�W�����v���ꂽ�Ƃ�
	if (yadd <= 1.0f)
	{
		//���Z����l��傫�����Ă���
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