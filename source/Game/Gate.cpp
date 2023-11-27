#include "header/Game/Gate.h"
#include "header/Collider/BoxCollider.h"
#include "easing/Easing.h"

Gate* Gate::Create(Model* model)
{
	//�C���X�^���X����
	Gate* instance = new Gate();
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

bool Gate::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	SetScale({ 1,15,20, });
	SetRotation({ 0,0,0 });
	SetPosition({ 0, 0, 0 });
	SetRadius({ radius.x,radius.y });
	//�R���C�_�[�̒ǉ�
	//���S���W�ƌ��_����̋���
	SetCollider(new BoxCollider(XMVECTOR({ 0,radius.y,0,0 }), radius));
	//���ʂ�ݒ肷��
	SetIdentification(IDENT_NEUTRAL);
	return true;
}

void Gate::Update()
{
	if (isGoal)
	{
		if (gateNum == 0)
		{
			//���������߂ɍ��W���擾
			position_[0] = {-25,-40,0};
			if (min <= max)
			{
				min += 0.01f;
			}
			y = min / max;
			position_[0].y = startY[0] + (endY - startY[0]) * Easing::easeOutQuint(y);

			SetPosition(position_[0]);
		}
		else if (gateNum == 1)
		{
			//���������߂ɍ��W���擾
			position_[1] = { -23, 40, 0 };

			if (min <= max)
			{
				min += 0.01f;
			}
			y = min / max;
			position_[1].y = startY[1] + (endY - startY[1]) * Easing::easeOutQuint(y);

			SetPosition(position_[1]);
		}
		if (position_[0].y == 0.0f && position_[1].y == 0.0f)
		{
			rotation.x++;
			if (rotation.x >= 90.0f)
			{
				rotation.x = 90.0f;
			}
		}
	}
	Object3d::Update();
}
