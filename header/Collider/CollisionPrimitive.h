#pragma once

#include <DirectXMath.h>

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

/// <summary>
/// 2DBox
/// </summary>
struct Box
{
	//���S�_
	DirectX::XMVECTOR center = { 0,0,0,1 };
	//�e���̃X�P�[��
	DirectX:: XMFLOAT2 radius = { 1.0f,1.0f };
};