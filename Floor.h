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
	//î•ñ(‘å‚«‚³,‰ñ“]Šp,À•W)
	XMFLOAT3 scale;
	XMFLOAT3 rotation;
	XMFLOAT3 position;
};

