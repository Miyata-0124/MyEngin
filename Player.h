#pragma once
#include "Object3D.h"
#include "Model.h"
#include "Input.h"

class Player
{
public:
	void Initialize(Model* model);
	void Update(Input* input);
	void Draw();
	//�s��
	void Move(Input* input);
private:
	Object3d* obj3d;
	//���(�傫��,��]�p,���W)
	XMFLOAT3 scale;
	XMFLOAT3 rotation;
	XMFLOAT3 position;
	//�ړ����x
	XMFLOAT3 moveSpeed;
	//�p���Ǘ��t���O
	bool downPosture;
};

