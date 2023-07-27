#include "Item.h"
#include "SphereCollider.h"

Item* Item::Create(Model* model)
{
	//�C���X�^���X����
	Item* instance = new Item();
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

bool Item::Initialize()
{

	if (!Object3d::Initialize())
	{
		return false;
	}
	//�������W�w��
	SetSize({ 0.5f,0.5f,0.5f });
	SetPosition({ 0,-10,0, });
	//�R���C�_�[�̒ǉ�
	//���a���������畂���Ă�����W�����S
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	return true;
}

void Item::Update()
{
	if (isRetention)
	{
		SetPosition({ playerPosition.x,playerPosition.y + radius,playerPosition.z });
		if (input->TriggerKey(DIK_X))
		{
			if (!isThrow)
			{
				isThrow = true;
			}
		}
	}
	if (isThrow)
	{
		if (throwTimer > 0.0f)
		{
			throwTimer -= 0.1f;
		}
		else
		{
			throwTimer = 3.0f;
		}
		if (throwTimer != 0)
		{
			position.x += throwSpeed;
		}
	}


	//�d��
	Gravity();
	Object3d::Update();
}

void Item::OnCollider(const CollisionInfo& info)
{
	//���ɓ��������Ȃ�
	if (info.collider->GetShapeType() == COLISIONSHAPE_PLANE)
	{
		yadd = 0.0f;
		isThrow = false;
	}
}

void Item::Gravity()
{
	if (isRetention == false)
	{
		position.y -= yadd;
		yadd += 0.2f;
	}
}
