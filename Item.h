#pragma once
#include "Object3D.h"
#include "Model.h"
#include "Input.h"
/// <summary>
/// 投擲出来るアイテム(石や槍など)
/// </summary>
class Item
{
public:
	void Initialize(Model* model);
	void Update();
	void Draw();
private:
	Object3d* obj3d;
	//情報(大きさ,回転角,座標)
	XMFLOAT3 scale;
	XMFLOAT3 rotation;
	XMFLOAT3 position;
};

