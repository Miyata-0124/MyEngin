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
	//�ێ������̋���
	RetentionThrow();
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

void Item::RetentionThrow()
{
	if (isRetention)
	{
		SetPosition({ playerPosition.x,playerPosition.y + radius,playerPosition.z });
		if (input->TriggerKey(DIK_X))
		{
			if (!isThrow && !input->PushKey(DIK_DOWN))
			{
				//�ō����B�_
				height = (throwSpeed * sin(30)) * (throwSpeed * sin(30)) / 2*g;
				//�ō����B����
				length = (throwSpeed * throwSpeed) * sin(30)*2 / g;
				isThrow = true;
			}
			if (input->PushKey(DIK_DOWN))
			{
				isRetention = false;
			}
		}
	}
	//�������ꂽ
	if (isThrow)
	{
		position.y += (float)height;
		position.x += (float)length;
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
