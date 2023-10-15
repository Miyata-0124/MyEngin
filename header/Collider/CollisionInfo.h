/**
 * @file CollisionInfo.h
 * @brief コライダーの情報を渡すための物
 * @author ミヤタ_コウキ
 * @date 2023/07/25
 */

#pragma once

#include <DirectXMath.h>
#pragma once

class Object3d;
class BaseCollider;

/// <summary>
/// 衝突情報
/// </summary>
class CollisionInfo
{
public:
	CollisionInfo(Object3d* object, BaseCollider* collider, const DirectX::XMVECTOR& inter) {
		this->object = object;
		this->collider = collider;
		this->inter = inter;
	}

	//衝突相手のオブジェクト
	Object3d* object = nullptr;
	//衝突相手のコライダー
	BaseCollider* collider = nullptr;
	//衝突点
	DirectX::XMVECTOR inter;
	//相手の属性

};

