/**
 * @file Floor.h
 * @brief ���E�̒�̔���@�\
 * @author �~���^_�R�E�L
 * @date 2023/07/09
 */

#pragma once
#include "header/3D/Object3D.h"
#include "header/3D/Model.h"
//�ł��Ⴂ�n�`�N���X

class Platform : public Object3d
{
public:
	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static Platform* Create(Model* model = nullptr);

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <returns></returns>
	bool Initialize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

	/// <summary>
	/// �R�[���o�b�N
	/// </summary>
	/// <param name="info"></param>
	void OnCollider(const CollisionInfo& info)override;

	void SetDistance(XMVECTOR distance_) { distance = distance_; }
private:
	//���_����̋���
	XMVECTOR distance = { 0, 0, 0 };
	//���a
	DirectX::XMFLOAT2 radius = { 60.0f,1.0f };
};

