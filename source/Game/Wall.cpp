#include "header/Game/Wall.h"
#include "header/Collider/BoxCollider.h"

using namespace DirectX;

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
	SetSize({ 1.0f,3.0f,1.0f });
	SetPosition({ 0,-12,0, });
	//�R���C�_�[�̒ǉ�
	//���a���������畂���Ă�����W�����S
	SetCollider(new BoxCollider(XMVECTOR({ 0,radius.y,0,0 }), radius));
	//���ʂ�ݒ肷��
	SetIdentification(IDENT_GATE);
	return true;
}

void Wall::Update()
{
	Object3d::Update();
}

void Wall::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{

	}
}
