#include "Player.h"

void Player::Initialize(Model* model)
{
	obj3d = Object3d::Create();
	obj3d->SetModel(model);
	obj3d->SetSize({ 1,1,1 });
	obj3d->SetPosition({ 0,0,0 });
	//���x
	moveSpeed = { 0.5f,0.5f,0.5f };//�ړ�
	accelSpeed = { 0.0f,0.0f };
	yadd = 0.0f;
	//��ԊǗ��t���O,�^�C�}�[
}

void Player::Update(Input* input)
{
	//���݂̏����擾
	scale = obj3d->GetScale();
	rotation = obj3d->GetRotation();
	position = obj3d->GetPosition();

	Move(input);
	Gravity();
	//�ύX��̒l��obj�ɓn��
	obj3d->SetSize(scale);
	obj3d->SetRotation(rotation);
	obj3d->SetPosition(position);
	obj3d->Update();
}

void Player::Draw()
{
	obj3d->Draw();
}

/// <summary>
/// �s��
/// </summary>
/// <param name="input">�L�[���</param>
void Player::Move(Input* input)
{
	//�擾�������ɒl��ǉ����Ă���
	if (input->PushKey(DIK_UP)) //�o��
	{
		//�����o�艺��\�ȃp�C�v���������Ȃ���W���グ��
	}
	if (input->TriggerKey(DIK_UP))
	{
		if (scale.y != 1)
		{
			scale = { 1,1,1 };
		}
		if (isCrouche)
		{
			position.y += 0.5f;
		}
		isCrouche = false;
	}
	if (input->PushKey(DIK_DOWN)) // ������
	{
		//�����o�艺��\�ȃp�C�v���������Ȃ���W��������
	}
	if (input->TriggerKey(DIK_DOWN))
	{
		if (scale.y != 0.5f)
		{
			scale = { 1,0.5,1 };
		}
		if (!isCrouche)
		{
			position.y -= 0.5f;
		}
		isCrouche = true;
	}
	if (input->PushKey(DIK_LEFT)) // ���Ɉړ�
	{
		position.x -= moveSpeed.x;
	}
	if (input->PushKey(DIK_RIGHT)) // �E�Ɉړ�
	{
		position.x += moveSpeed.x;
	}
	if (input->TriggerKey(DIK_SPACE)) // �W�����v���X���C�h
	{
		CrouchMove(input);
	}
}

void Player::CrouchMove(Input* input)
{
	if (isCrouche == false && isJump == false)
	{
		yadd = -1.0f;
		isJump = true;
	}
	if (isCrouche == true)
	{

	}
}

void Player::Gravity()
{
	position.y -= yadd;
	yadd += 0.2f;
	if (position.y<=-5.0f)
	{
		yadd = 0.0f;
		if (isJump)
		{
			isJump = false;
		}
	}
}
