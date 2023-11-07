#pragma once
#include "header/3D/Object3D.h"

class ClearBox : public Object3d
{
public:
	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static ClearBox* Create(Model* model = nullptr);

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

	bool GetIsGoal() { return isGoal; }

private:
	//���a
	DirectX::XMFLOAT2 radius = { 10.0f,5 };

	bool isGoal = false;
};

