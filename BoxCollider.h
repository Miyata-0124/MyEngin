#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include <DirectXMath.h>

class BoxCollider: public BaseCollider , public Box
{
private: //エイリアス
	//DirectXを省略
	using XMVECTOR = DirectX::XMVECTOR;
public:
	BoxCollider(XMVECTOR offset = { 0,0,0,0 }, float radius = 0.0f) :offset(offset), radius(radius)
	{
		//形状セット
		shapeType = COLISIONSHAPE_BOX;
	}
	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	inline void SetRadius(float distance) { this->radius = distance; }

private:
	//オブジェクト中心
	XMVECTOR offset;
	//原点からの距離
	float radius;
};

