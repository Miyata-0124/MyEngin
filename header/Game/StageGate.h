#pragma once
//�}�b�v�ړ�����p�I�u�W�F�N�g

#include "header/3D/Object3D.h"

class StageGate : public Object3d
{
public:
	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static StageGate* Create(Model* model = nullptr);

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

private:
	//���a
	DirectX::XMFLOAT2 radius = { Object3d::GetScale().x,Object3d::GetScale().y};

	//�ړ��̏����n�_
	XMVECTOR startPos = {};
	//�ړ���̓����X
	XMVECTOR endPos = {};
	//�ŏ�
	float min = 0.0f;
	//�ő�
	float max = 1.0f;
};

