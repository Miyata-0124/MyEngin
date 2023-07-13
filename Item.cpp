#include "Item.h"
#include "SphereCollider.h"

Item* Item::Create(Model* model)
{
	//�C���X�^���X����
	Item* instance = new Item();
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

bool Item::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//�����T�C�Y�ݒ�
	SetSize({ 0.5f,0.5f,0.5f });
	//�������W�w��
	SetPosition({ 0,0,0, });
	//�R���C�_�[�̒ǉ�
	//���a���������畂���Ă�����W�����S
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	return true;
}

void Item::Update()
{
	//�d��
	Gravity();
	Object3d::Update();
}

void Item::OnCollider(const CollisionInfo& info)
{
	//���ɓ��������Ȃ�
	if (info.collider->GetShapeType() == COLISIONSHAPE_PLANE)
	{
		yadd = 0.0f;
	}
}

void Item::Gravity()
{
	position.y -= yadd;
	yadd += 0.2f;
}
