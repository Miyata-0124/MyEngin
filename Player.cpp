#include "Player.h"

void Player::Initialize(Model* model)
{
	obj3d = Object3d::Create();
	obj3d->SetModel(model);
	obj3d->SetSize({ 2,2,2 });
	obj3d->SetPosition({ 0,0,0 });
	//�ړ����x
	moveSpeed = { 0.5f,0.5f,0.5f };
	//�p���Ǘ��t���O
	downPosture = false;
}

void Player::Update(Input* input)
{
	Move(input);
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
	//���݂̍��W���擾
	position = obj3d->GetPosition();
	//�擾�������ɒl��ǉ����Ă���
	if (input->PushKey(DIK_UP)) //�o��
	{
		//�����o�艺��\�ȃp�C�v���������Ȃ���W���グ��
	}
	if (input->PushKey(DIK_DOWN)) // ������
	{
		//�����o�艺��\�ȃp�C�v���������Ȃ���W��������
	}
	if (input->PushKey(DIK_LEFT)) // ���Ɉړ�
	{
		position.x -= moveSpeed.x;
	}
	if (input->PushKey(DIK_RIGHT)) // �E�Ɉړ�
	{
		position.x += moveSpeed.x;
	}
	if (input->TriggerKey(DIK_SPACE)) // �W�����v
	{

	}
	//�ύX��̒l��obj�ɓn��
	obj3d->SetPosition({ position.x,position.y,position.z });
}
