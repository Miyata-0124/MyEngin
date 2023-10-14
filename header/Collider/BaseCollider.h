#pragma once
#include "CollisionTypes.h"
#include "CollisionInfo.h"
#include "header/3D/Object3D.h"

class BaseCollider
{
public:
	BaseCollider() = default;
	//���z�f�X�g���N�^
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
	//�`��^�C�v
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
};

