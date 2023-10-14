#pragma once
#include "CollisionTypes.h"
#include "CollisionInfo.h"
#include "header/3D/Object3D.h"

class BaseCollider
{
public:
	BaseCollider() = default;
	//仮想デストラクタ
	virtual ~BaseCollider() = default;

	inline void SetObject(Object3d* object) {
		this->object3d = object;
	}

	inline Object3d* GetObject3d() {
		return object3d;
	}

	inline void OnCollision(const CollisionInfo& info) {
		object3d->OnCollider(info);
	}
	virtual void Update() = 0;

	inline CollisionShapeType GetShapeType() { return shapeType; }
protected:
	Object3d* object3d = nullptr;
	//形状タイプ
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
};

