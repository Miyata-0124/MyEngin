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
		//���������߂ɍ��W���擾
		startY = position.y;
		if (min <= max)
		{
			min += 0.01f;
		}
		y = min / max;
		position.y = startY + (endY - startY) * Easing::easeOutQuint(y);

		SetPosition(position);

		if (position.y == 0.0f)
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
