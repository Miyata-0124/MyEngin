#include "header/Game/Pipe.h"
#include "header/Collider/SphereCollider.h"

Pipe* Pipe::Create(Model* model)
{
	//�C���X�^���X����
	Pipe* instance = new Pipe();
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

bool Pipe::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//�������W�w��
	SetScale({ 1,1,1 });
	SetRotation({ 0,90,0 });
	SetPosition({ 0,0,0, });
	SetRadius({ 3.0f,3.0f });
	//�R���C�_�[�̒ǉ�
	//���a���������畂���Ă�����W�����S
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius.y,0,0 }), radius.y));
	//���ʂ�ݒ肷��
	SetIdentification(IDENT_PIPE);
	return true;
}

void Pipe::Update()
{
	Object3d::Update();
}

void Pipe::OnCollider(const CollisionInfo& info)
{
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{

	}
}
