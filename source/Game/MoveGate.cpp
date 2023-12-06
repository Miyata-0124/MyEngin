#include "header/Game/MoveGate.h"
#include "header/Collider/BoxCollider.h"

MoveGate* MoveGate::Create(Model* model)
{
	//�C���X�^���X����
	MoveGate* instance = new MoveGate();
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

bool MoveGate::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//�������W�w��
	SetScale({ 1,1,1 });
	SetRotation({ 0,0,0 });
	SetPosition({ 30,-7,0 });
	SetRadius({ radius.x,radius.y });
	//�R���C�_�[�̒ǉ�
	//���a���������畂���Ă�����W�����S
	SetCollider(new BoxCollider(XMVECTOR({ 0,radius.y,0,0 }), radius));
	//���ʂ�ݒ肷��
	SetIdentification(IDENT_GATE);
	return true;
}

void MoveGate::Update()
{
	Object3d::Update();
}

void MoveGate::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{
		if (info.object->GetIdentification() == IDENT_PLAYER)
		{
			if (input->TriggerKey(DIK_V))
			{
				isMapMove = true;
			}
		}
	}
}
