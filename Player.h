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
	//行動
	void Move(Input* input);
private:
	Object3d* obj3d;
	//情報(大きさ,回転角,座標)
	XMFLOAT3 scale;
	XMFLOAT3 rotation;
	XMFLOAT3 position;
	//移動速度
	XMFLOAT3 moveSpeed;
	//姿勢管理フラグ
	bool downPosture;
};

