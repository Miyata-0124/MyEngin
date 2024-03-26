#include "header/Game/APBox.h"
#include "header/Collider/BoxCollider.h"

APBox* APBox::Create(Model* model)
{
	//�C���X�^���X����
	APBox* instance = new APBox();
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

bool APBox::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//�������W�w��
	SetScale({ 1,1,1 });
	SetRotation({ 0,0,0 });
	SetPosition({ 0,0,0 });
	SetRadius({ 2.0f,2.0f });
	//�R���C�_�[�̒ǉ�
	//���a���������畂���Ă�����W�����S
	SetCollider(new BoxCollider(XMVECTOR({ 0,GetRadius().y,0,0}), GetRadius()));
	//���ʂ�ݒ肷��
	SetIdentification(IDENT_ITEM);

	return true;
}

void APBox::Update()
{
    Object3d::Update();
}

void APBox::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{
		//�v���C���[���I�u�W�F�N�g�ɓ���������
		if (info.object->GetIdentification() == IDENT_PLAYER)
		{
			//�����󂯂�A�j���[�V������ǉ�����
		}
	}
}
