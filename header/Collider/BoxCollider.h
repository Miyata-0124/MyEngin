/**
 * @file BoxCollider.h
 * @brief 2D�l�p�`�̃A�^������
 * @author �~���^_�R�E�L
 * @date 2023/10/10
 */

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
	BoxCollider(XMVECTOR center = { 0,0,0,0 }, XMFLOAT2 radius = { 1.0f,1.0f }) :center(center), radius(radius)
	{
		//�`��Z�b�g
		shapeType = COLISIONSHAPE_BOX;
	}
	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

	inline void SetRadius(XMFLOAT2 radius_) { this->radius = radius_; }

private:
	//�I�u�W�F�N�g���S
	XMVECTOR center;
	//���a
	XMFLOAT2 radius;
};

