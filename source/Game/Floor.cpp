#include "header/Game/Floor.h"
#include "header/Collider/BoxCollider.h"

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
	SetSize({ 80,1,20, });
	SetPosition({ 0, -15, 0 });
	//�R���C�_�[�̒ǉ�
	//���S���W�ƌ��_����̋���
	SetCollider(new BoxCollider(XMVECTOR({ 0,radius.y,0,0 }), radius));
	return true;
}

void Floor::Update()
{
	Object3d::Update();
}

void Floor::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{

	}
}
