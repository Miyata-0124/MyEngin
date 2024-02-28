#include "header/Game/Wall.h"
#include "header/Collider/BoxCollider.h"

using namespace DirectX;

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
	//�������W�w��
	SetScale({ 1,1,1});
	SetRotation({ 0,90,0 });
	SetPosition({ 0,0,0, });
	SetRadius({ 5.0f,5.0f });
	//�R���C�_�[�̒ǉ�
	//���a���������畂���Ă�����W�����S
	SetCollider(new BoxCollider(XMVECTOR({ 0,GetRadius().y,0,0}), GetRadius()));
	//���ʂ�ݒ肷��
	SetIdentification(IDENT_FLOOR);
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
