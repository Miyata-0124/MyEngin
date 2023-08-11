#pragma once

#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include <DirectXMath.h>

class SphereCollider:public BaseCollider,public Sphere
{
public:
	SphereCollider(Vector3 offset = { 0,0,0 }, float radius = 1.0f) :offset(offset), radius(radius)
	{
		//形状セット
		shapeType = COLISIONSHAPE_SPHERE;
	}
	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	inline void SetRadius(float radius) { this->radius = radius; }

private:
	//オブジェクト中心
	Vector3 offset;
	//半径
	float radius;
};

