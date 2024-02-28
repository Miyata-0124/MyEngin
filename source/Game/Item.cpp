#include "header/Game/Item.h"
#include "header/Collider/BoxCollider.h"

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
	SetScale({ 2.0f,0.5f,0.5f });
	SetRotation({ 0,0,0 });
	SetPosition({ -60,0,0, });
	SetRadius({ radius.x,radius.y });
	//�R���C�_�[�̒ǉ�
	//���a���������畂���Ă�����W�����S
	SetCollider(new BoxCollider(XMVECTOR({ 0,GetRadius().y,0,0}), GetRadius()));
	//���ʂ�ݒ肷��
	SetIdentification(IDENT_ITEM);
	return true;
}

void Item::Update()
{
	//�ێ������̋���
	RetentionThrow();
	//�A�C�e�����v���C���[�̎��ӂɈړ�������
	Remove();
	//�A�C�e���̏�Ԃ��h�����Ă��邩�ǂ���
	//�h�����Ă��Ȃ��Ȃ�
	if (!isStop)
	{
		//�d�͂𑫂��Ă���
		Gravity();
	}
	else
	{
		if (isRetention)
		{
			isStop = false;
		}
	}

	if (position.y <= -50)
	{
		height = 0.0f;
		length = 0.0f;
		position = { -10,5,0, };
	}

	Object3d::Update();
}

void Item::OnCollider(const CollisionInfo& info)
{
	//���ɓ��������Ȃ�
	if (info.collider->GetShapeType() == COLISIONSHAPE_PLANE)
	{
		//�����ȃI�u�W�F�N�g�ɓ���������
		if (info.object->GetIdentification() == IDENT_NEUTRAL)
		{
			yadd = 0.0f;
			isThrow = false;
		}
		//�A�C�e���ɓ���������
		if (info.object->GetIdentification() == IDENT_ITEM)
		{

		}
		//�G���I�u�W�F�N�gor�G�ɓ���������
		if (info.object->GetIdentification() == IDENT_ENEMY)
		{

		}
		
	}
	if (info.collider->GetShapeType() == COLISIONSHAPE_SPHERE)
	{
		//�����ȃI�u�W�F�N�g�ɓ���������
		if (info.object->GetIdentification() == IDENT_NEUTRAL)
		{
			yadd = 0.0f;
			isThrow = false;
		}
		//�A�C�e���ɓ���������
		if (info.object->GetIdentification() == IDENT_ITEM)
		{

		}
		//�G���I�u�W�F�N�gor�G�ɓ���������
		if (info.object->GetIdentification() == IDENT_ENEMY)
		{

		}
		//�v���C���[���������Ă���Ƃ�
		if (info.object->GetIdentification() == IDENT_PLAYER)
		{
			yadd = 0.0f;
			isThrow = false;
		}
	}
	if (info.collider->GetShapeType() == COLISIONSHAPE_BOX)
	{
		//�����ȃI�u�W�F�N�g�ɓ���������
		if (info.object->GetIdentification() == IDENT_NEUTRAL)
		{
			yadd = 0.0f;
			isThrow = false;
		}
		//�A�C�e���ɓ���������
		if (info.object->GetIdentification() == IDENT_ITEM)
		{

		}
		//�G���I�u�W�F�N�gor�G�ɓ���������
		if (info.object->GetIdentification() == IDENT_ENEMY)
		{

		}
		if (info.object->GetIdentification() == IDENT_FLOOR)
		{
			//�ǂɓ����������̏ꏊ��ۑ�����ϐ�
			float stopPos = position.y;
			yadd = 0.0f;
			if (isThrow)
			{
				height = 0.0f;
				length = 0.0f;
				if (position.y < info.object->GetPosition().y + info.object->GetRadius().y)
				{
					if (isDirection)//��
					{
						position.x = info.object->GetPosition().x + info.object->GetRadius().x + radius.x;
					}
					else//�E
					{
						position.x = info.object->GetPosition().x - info.object->GetRadius().x - radius.x;
					}
					//���W�̍�����ۑ������ꏊ�ɌŒ肷��
					position.y = stopPos;

					isStop = true;
				}
			}
		}
	}
}

void Item::RetentionThrow()
{
	if (isRetention)
	{
		SetRotation({ 0,0,0 });
		if (isDirection)
		{
			SetPosition({ playerPosition.x,playerPosition.y + radius.y ,playerPosition.z + radius.y });
		}
		else
		{
			SetPosition({ playerPosition.x,playerPosition.y + radius.y ,playerPosition.z - radius.y });
		}
		
		if (input->TriggerKey(DIK_X))
		{
			if (!isThrow && !input->PushKey(DIK_DOWN))
			{
				ThrowLength();
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

void Item::Remove()
{
	
}

void Item::Gravity()
{
	if (isRetention == false)
	{
		position.y -= yadd;
		yadd += 0.2f;
	}
}

void Item::ThrowLength()
{
	//������ꂽ���̏d�͉��Z
	//�A�C�e���{�̂ɂ��Ă���̂Ƃ͕ʕ�
	float g = 0.80f;
	//������
	if (isDirection)
	{
		//�ō����B�_
		height = (throwSpeed * sin(30)) * (throwSpeed * sin(30)) / 2 * g;
		//�ō����B����
		length = (throwSpeed * throwSpeed) * sin(30) * 2 / g;
	}
	//�E����
	else
	{//�ō����B�_
		height = (throwSpeed * sin(30)) * (throwSpeed * sin(30)) / 2 * g;
		//�ō����B����
		length = -((throwSpeed * throwSpeed) * sin(30) * 2 / g);

	}
}