#pragma once

#include <DirectXMath.h>
#include "Vector3.h"

/// <summary>
/// ��
/// </summary>
struct Sphere
{
	//���S�_
	DirectX::XMVECTOR center = { 0,0,0,1 };
	//���a
	float radius = 1.0f;
};

/// <summary>
/// ����
/// </summary>
struct Plane
{
	//�@���x�N�g��
	DirectX::XMVECTOR normal = { 0,1,0,0 };
	//���_����̋���
	float distance = 0.0f;
};

/// <summary>
/// ���C(������)
/// </summary>
struct Ray
{
	//���_���W
	DirectX::XMVECTOR start = { 0,0,0,1 };
	//����
	DirectX::XMVECTOR dir = { 1,0,0,0 };
};

struct OBB
{
public:
	Vector3 Pos;              // �ʒu
	Vector3 NormaDirect[3];   // �����x�N�g��
	float fLength[3];             // �e�������̒���

	OBBPlane plane[6];
};
struct OBBPlane {
	//�@���x�N�g��
	Vector3 normal = { 0,1,0 };
	//���_(0,0,0)����̋���
	float distance = 0.0f;

	Vector3 vertex[4];
	Vector3 pos = { 0,0,0 };
};