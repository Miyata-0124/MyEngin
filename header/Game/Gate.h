#pragma once
#include "header/3D/Object3D.h"

class Gate : public Object3d
{
public:
	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static Gate* Create(Model* model = nullptr);

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

	//�Q�[�g�i���o�[�̐ݒ�
	void SetGateNum(int32_t gateNum_) { this->gateNum = gateNum_; }
	void SetIsGoal(bool isGoal_) { this->isGoal = isGoal_; }

	bool GetIsGoal() { return isGoal; }
private:
	int32_t gateNum;

	XMFLOAT3 position_[2];
	//���a
	DirectX::XMFLOAT2 radius = { 1.0f,1.0f };

	bool isGoal = false;
	//�C�[�W���O�p
	float min = 0.0f;
	float max = 1.0f;
	float startY[2] = { -40.0f,40.0f };
	float endY = 0.0f;
	float y;
};