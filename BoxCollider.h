#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include <DirectXMath.h>

class BoxCollider :public BaseCollider, public Box
{
private: //�G�C���A�X
	//DirectX���ȗ�
	using XMVECTOR = DirectX::XMVECTOR;
public:
	BoxCollider(XMVECTOR center = { 0,0,0,1 } , float radius = 1.0f) :center(center),radius(radius)
	{
		//�`��Z�b�g
		shapeType = COLISIONSHAPE_BOX;
	}
	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

	inline void SetRadius(float radius) { this->radius = radius; }

private:
	//�I�u�W�F�N�g���S
	XMVECTOR center;
	//���_����̋���
	float point[4];
	float radius;
};

