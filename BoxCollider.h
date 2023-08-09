#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include <DirectXMath.h>

class BoxCollider: public BaseCollider , public Box
{
private: //�G�C���A�X
	//DirectX���ȗ�
	using XMVECTOR = DirectX::XMVECTOR;
public:
	BoxCollider(XMVECTOR offset = { 0,0,0,0 }, float radius = 0.0f) :offset(offset), radius(radius)
	{
		//�`��Z�b�g
		shapeType = COLISIONSHAPE_BOX;
	}
	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

	inline void SetRadius(float distance) { this->radius = distance; }

private:
	//�I�u�W�F�N�g���S
	XMVECTOR offset;
	//���_����̋���
	float radius;
};

