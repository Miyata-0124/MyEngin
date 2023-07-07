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
	//しゃがみの行動
	void CrouchMove(Input* input);
	//重力
	void Gravity();
	//Getter,Setter
	XMFLOAT3 GetPosition() { return position; }

	XMMATRIX GetMatWorld() { return obj3d->GetMatWorld(); }
private:
	Object3d* obj3d;
	//情報(大きさ,回転角,座標)
	XMFLOAT3 scale;
	XMFLOAT3 rotation;
	XMFLOAT3 position;
	//速度
	XMFLOAT3 moveSpeed;//移動
	XMFLOAT2 accelSpeed;//加速速度
	float yadd;//重力

	//状態管理フラグ,タイマー
	bool isCrouche = false;
	bool isJump = false;
};

