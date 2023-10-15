/**
 * @file SphereCollider.h
 * @brief ����̃R���C�_�[����
 * @author �~���^_�R�E�L
 * @date 2023/07/25
 */

#pragma once

#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include <DirectXMath.h>

class SphereCollider :public BaseCollider, public Sphere
{
private: //�G�C���A�X
	//DirectX���ȗ�
	using XMVECTOR = DirectX::XMVECTOR;
public:
	SphereCollider(XMVECTOR offset = { 0,0,0,0 }, float radius = 1.0f) :offset(offset), radius(radius)
	{
		//�`��Z�b�g
		shapeType = COLISIONSHAPE_SPHERE;
	}
	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

	inline void SetRadius(float radius_) { this->radius = radius_; }

private:
	//�I�u�W�F�N�g���S
	XMVECTOR offset;
	//���a
	float radius;
};