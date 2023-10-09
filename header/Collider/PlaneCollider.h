#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include <DirectXMath.h>

class PlaneCollider :public BaseCollider, public Plane
{
private: //エイリアス
	//DirectXを省略
	using XMVECTOR = DirectX::XMVECTOR;
public:
	PlaneCollider(XMVECTOR offset = { 0,0,0,0 }, float distance = 0.0f) :offset(offset), distance(distance)
	{
		//形状セット
		shapeType = COLISIONSHAPE_PLANE;
	}
	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	inline void SetDistance(float distance_) { this->distance = distance_; }

private:
	//オブジェクト中心
	XMVECTOR offset;
	//原点からの距離
	float distance;
};

