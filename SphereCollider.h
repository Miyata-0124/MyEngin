#pragma once

#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include <DirectXMath.h>

class SphereCollider:public BaseCollider,public Sphere
{
private: //エイリアス
	//DirectXを省略
	using XMVECTOR = DirectX::XMVECTOR;
public:
	SphereCollider(XMVECTOR offset = { 0,0,0,0 }, float radius = 1.0f) :offset(offset), radius(radius)
	{
		//形状セット
		shapeType = COLISIONSHAPE_SPHERE;
	}
	
	void Update()override;

	inline void SetRadius(float radius) { this->radius = radius; }

private:
	//オブジェクト中心
	XMVECTOR offset;
	//半径
	float radius;
};

