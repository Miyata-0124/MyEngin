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
private:
	DirectX::XMVECTOR center; //���S���W
	DirectX::XMVECTOR normaDirect[3]; //�����x�N�g��
	float fLength[3]; //�e�������̒���
public:
	XMVECTOR GetDirect(uint32_t elem); //�w�莲�ԍ��̕����x�N�g�����擾
	float GetLen(uint32_t elem); //�w�莲�����̒������擾
	XMVECTOR GetCenter();
};