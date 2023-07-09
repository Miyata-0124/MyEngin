#include "Floor.h"
#include "PlaneCollider.h"

Floor* Floor::Create(Model* model)
{
	//�C���X�^���X����
	Floor* instance = new Floor();
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

bool Floor::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//�R���C�_�[�̒ǉ�
	float distance = 0.0f;
	//���a���������畂���Ă�����W�����S
	SetCollider(new PlaneCollider(XMVECTOR({ 0,1,0,0 }), distance));
	return true;
}

void Floor::Update()
{
	Object3d::Update();
}

void Floor::OnCollider(const CollisionInfo& info)
{

}
