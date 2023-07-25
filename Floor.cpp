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
	SetSize({ 80,1,80, });
	SetPosition({ 0, -15, 0 });
	//�R���C�_�[�̒ǉ�
	//���S���W�ƌ��_����̋���
	SetCollider(new PlaneCollider(XMVECTOR({ radius.m128_f32[0],radius.m128_f32[1],radius.m128_f32[2],0}), distance));
	return true;
}

void Floor::Update()
{
	Object3d::Update();
}

void Floor::OnCollider(const CollisionInfo& info)
{

}
