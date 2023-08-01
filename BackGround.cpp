#include "BackGround.h"

BackGround* BackGround::Create(Model* model)
{
	//�C���X�^���X����
	BackGround* instance = new BackGround();
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

bool BackGround::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}
	//�������W�w��
	SetSize({ 100,100,100 });
	SetPosition({ 0,0,0, });
	return true;
}

void BackGround::Update()
{
	Object3d::Update();
}
