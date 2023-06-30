#pragma once
#include "Object3D.h"
#include "Model.h"

class Floor
{
public:
	void Initialize(Model* model);
	void Update();
	void Draw();
private:
	Object3d* obj3d;
	//���(�傫��,��]�p,���W)
	XMFLOAT3 scale;
	XMFLOAT3 rotation;
	XMFLOAT3 position;
};

