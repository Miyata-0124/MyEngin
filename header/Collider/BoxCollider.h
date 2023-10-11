#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include <DirectXMath.h>

class BoxCollider :public BaseCollider, public Box
{
private: //エイリアス
	//DirectXを省略
	using XMVECTOR = DirectX::XMVECTOR;
public:
	BoxCollider(XMVECTOR center = { 0,0,0,0 }, XMFLOAT2 radius = { 1.0f,1.0f }) :center(center), radius(radius)
	{
		//形状セット
		shapeType = COLISIONSHAPE_BOX;
	}
	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	inline void SetRadius(XMFLOAT2 radius) { this->radius = radius; }

private:
	//オブジェクト中心
	XMVECTOR center;
	//半径
	XMFLOAT2 radius;
};

