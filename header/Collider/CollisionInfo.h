/**
 * @file CollisionInfo.h
 * @brief �R���C�_�[�̏���n�����߂̕�
 * @author �~���^_�R�E�L
 * @date 2023/07/25
 */

#pragma once

#include <DirectXMath.h>
#pragma once

class Object3d;
class BaseCollider;

/// <summary>
/// �Փˏ��
/// </summary>
class CollisionInfo
{
public:
	CollisionInfo(Object3d* object, BaseCollider* collider, const DirectX::XMVECTOR& inter) {
		this->object = object;
		this->collider = collider;
		this->inter = inter;
	}

	//�Փˑ���̃I�u�W�F�N�g
	Object3d* object = nullptr;
	//�Փˑ���̃R���C�_�[
	BaseCollider* collider = nullptr;
	//�Փ˓_
	DirectX::XMVECTOR inter;
	//����̑���

};

