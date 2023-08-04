#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include <DirectXMath.h>

class OBBCollider :public BaseCollider, public OBB
{
private: //エイリアス
	//DirectXを省略
	using XMVECTOR = DirectX::XMVECTOR;
public:
	OBBCollider(XMVECTOR offset = { 0,0,0,0 }, XMVECTOR size = { 0,0,0,0 }, XMVECTOR rot[3] = 0)
	{
		//形状セット
		shapeType = COLISIONSHAPE_OBB;
	}
	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

private:
	//中心座標
	XMVECTOR center = { 0,0,0,1 };
	//各座標軸の傾きベクトル
	XMVECTOR rot[3] = { 0,0,0,0 };
	//OBB座標軸の長さ半分
	XMVECTOR size = { 1,1,1,1 };
};


