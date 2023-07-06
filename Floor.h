#pragma once
#include "Object3D.h"
#include "Model.h"

class Floor
{
public:
	void Initialize(Model* model);
	void Update();
	void Draw();

	//Getter,Setter
	XMFLOAT3 GetPosition() { return position; }

	XMMATRIX GetMatWorld() { return obj3d->GetMatWorld(); }
private:
	Object3d* obj3d;
	//î•ñ(‘å‚«‚³,‰ñ“]Šp,À•W)
	XMFLOAT3 scale;
	XMFLOAT3 rotation;
	XMFLOAT3 position;
};

