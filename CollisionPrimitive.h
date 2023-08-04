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

//�����̂̔�
struct OBB
{
	//���S���W
	DirectX::XMVECTOR center = { 0,0,0,1 };
	//�e���W���̌X�������x�N�g��
	DirectX::XMVECTOR rot[3] = { 0,0,0,0 };
	//OBB���W���̒�������
	DirectX::XMVECTOR size = { 1,1,1,1 };
};