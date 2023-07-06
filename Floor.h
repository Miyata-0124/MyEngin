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
	//情報(大きさ,回転角,座標)
	XMFLOAT3 scale;
	XMFLOAT3 rotation;
	XMFLOAT3 position;
};

