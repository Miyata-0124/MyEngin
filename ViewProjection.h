#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include "Math.h"

class ViewProjection
{
public:
	Matrix4 matView;
	Vector3 eye;	//視点座標
	Vector3 target = { 0,0,0 };	//注視点座標
	Vector3 up;		//上方向ベクトル

public:
	void Initialize();
	void UpdateViewPro();
};

