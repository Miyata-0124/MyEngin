#include "header/Game/Floor.h"
#include "header/Collider/PlaneCollider.h"

Platform* Platform::Create(Model* model)
{
	//�C���X�^���X����
	Platform* instance = new Platform();
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

bool Platform::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	SetScale({ 60,1,60, });
	SetRotation({ 0,0,0 });
	SetPosition({ 0, -15, 0 });
	SetRadius({ radius.x,radius.y });
	//�R���C�_�[�̒ǉ�
	SetDistance({ position.x, position.y + radius.y+radius.y, position.z });
	//���S���W�ƌ��_����̋���
	SetCollider(new PlaneCollider(XMVECTOR({ 0,position.y + radius.y,0,0 }), distance.m128_f32[1]));
	//���ʂ�ݒ肷��
	SetIdentification(IDENT_NEUTRAL);
	return true;
}

void Platform::Update()
{
	Object3d::Update();
}

void Platform::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{

	}
}
