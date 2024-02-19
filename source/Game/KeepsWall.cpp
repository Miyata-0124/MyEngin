#include "header/Game/KeepsWall.h"
#include "header/Collider/BoxCollider.h"

KeepsWall* KeepsWall::Create(Model* model)
{
	//�C���X�^���X����
	KeepsWall* instance = new KeepsWall();
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

bool KeepsWall::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//�������W�w��
	SetScale({ 1,1,1 });
	SetRotation({ 0,0,0 });
	SetPosition({ 0,0,0, });
	SetRadius({ 10,20 });
	//�R���C�_�[�̒ǉ�
	//���a���������畂���Ă�����W�����S
	SetCollider(new BoxCollider(XMVECTOR({ 0,GetRadius().y,0,0}), GetRadius()));
	//���ʂ�ݒ肷��
	SetIdentification(IDENT_WALL);
	return true;
}

void KeepsWall::Update()
{
	Object3d::Update();
}

void KeepsWall::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{

	}
}
