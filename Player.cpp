#include "Player.h"

void Player::Initialize(Model* model)
{
	obj3d = Object3d::Create();
	obj3d->SetModel(model);
	obj3d->SetSize({ 2,2,2 });
	obj3d->SetPosition({ 0,0,0 });
	//���x
	moveSpeed = { 0.5f,0.5f,0.5f };//�ړ�
	accelSpeed = { 0.0f,0.0f };
	yadd = { 0,0 };
	//��ԊǗ��t���O,�^�C�}�[
}

void Player::Update(Input* input,bool isHit)
{
	//���݂̏����擾
	scale = obj3d->GetScale();
	rotation = obj3d->GetRotation();
	position = obj3d->GetPosition();

	Move(input);
	Gravity(isHit);
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
		if (scale.y != 2)
		{
			scale = { 2,2,2 };
		}
		if (isCrouche)
		{
			position.y += 1;
		}
		isCrouche = false;
	}
	if (input->PushKey(DIK_DOWN)) // ������
	{
		//�����o�艺��\�ȃp�C�v���������Ȃ���W��������
	}
	if (input->TriggerKey(DIK_DOWN))
	{
		if (scale.y != 1)
		{
			scale = { 2,1,2 };
		}
		if (!isCrouche)
		{
			position.y -= 1;
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
		yadd.y = -2.0f;
		isJump = true;
	}
	if (isCrouche == true)
	{

	}
}

void Player::Gravity(bool ishit)
{
	position.y -= yadd.y;
	yadd.y += 0.2f;
	if (position.y<=-5.0f)
	{
		yadd.y = 0.0f;
		if (isJump)
		{
			isJump = false;
		}
	}
}
