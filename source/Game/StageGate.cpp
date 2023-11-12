#include "header/Game/StageGate.h"
#include "header/Collider/BoxCollider.h"

StageGate* StageGate::Create(Model* model)
{
	//�C���X�^���X����
	StageGate* instance = new StageGate();
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

bool StageGate::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//�������W�w��
	SetSize({ 2,2,2 });
	SetRotation({ 0,0,0 });
	SetPosition({ 40,-13,0 });
	//�R���C�_�[�̒ǉ�
	//���a���������畂���Ă�����W�����S
	SetCollider(new BoxCollider(XMVECTOR({ 0,radius.y,0,0 }), radius));
	//���ʂ�ݒ肷��
	SetIdentification(IDENT_GATE);
	return true;
}

void StageGate::Update()
{
	Object3d::Update();
}

void StageGate::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{

	}
}
