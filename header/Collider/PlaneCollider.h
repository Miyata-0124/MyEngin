#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include <DirectXMath.h>

class PlaneCollider :public BaseCollider, public Plane
{
private: //�G�C���A�X
	//DirectX���ȗ�
	using XMVECTOR = DirectX::XMVECTOR;
public:
	PlaneCollider(XMVECTOR offset = { 0,0,0,0 }, float distance = 0.0f) :offset(offset), distance(distance)
	{
		//�`��Z�b�g
		shapeType = COLISIONSHAPE_PLANE;
	}
	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

	inline void SetDistance(float distance) { this->distance = distance; }

private:
	//�I�u�W�F�N�g���S
	XMVECTOR offset;
	//���_����̋���
	float distance;
};

