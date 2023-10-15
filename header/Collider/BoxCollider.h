/**
 * @file BoxCollider.h
 * @brief 2D四角形のアタリ判定
 * @author ミヤタ_コウキ
 * @date 2023/10/10
 */

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

	inline void SetRadius(XMFLOAT2 radius_) { this->radius = radius_; }

private:
	//オブジェクト中心
	XMVECTOR center;
	//半径
	XMFLOAT2 radius;
};

