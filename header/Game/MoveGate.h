#pragma once
#include "header/3D/Object3D.h"
#include "header/Engin/Input.h"

class MoveGate : public Object3d
{
public:
	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static MoveGate* Create(Model* model = nullptr);

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

	/// <summary>
	/// �L�[���Z�b�g
	/// </summary>
	/// <param name="input">�L�[���</param>
	/// <returns></returns>
	Input* SetInput(Input* input_) { return this->input = input_; }

	bool GetMapMove() { return isMapMove; }
	void SetMapMove(bool isMapMove_) { isMapMove = isMapMove_; }
private:
	Input* input = nullptr;
private:
	//���a
	XMFLOAT2 radius = { 1.0f,1.0f };

	//�t���O
	bool isMapMove = false;
};

