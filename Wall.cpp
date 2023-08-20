#include "Wall.h"
#include "SphereCollider.h"

Wall* Wall::Create(Model* model)
{
	//�C���X�^���X����
	Wall* instance = new Wall();
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

bool Wall::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//�������W�w��
	SetSize({ 3.0f,3.0f,3.0f });
	SetPosition({ 0,-13,0, });
	//�R���C�_�[�̒ǉ�
	//���a���������畂���Ă�����W�����S
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	return true;
}

void Wall::Update()
{
	Object3d::Update();
}

void Wall::OnCollider(const CollisionInfo& info)
{
}
