#pragma once
#include "Object3D.h"
#include "Input.h"

class Player : public Object3d
{
public:
	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static Player* Create(Model* model = nullptr);

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

	//�L�[�����Z�b�g
	Input* SetInput(Input* input) { return this->input = input; }
private:
	//���E�ړ�
	void Move();
	//�W�����v
	void Jamp();
	//�d��
	void Gravity();

private:
	Input* input = nullptr;
private:
	float yadd;
	float radius = 0.6f;
};

