#pragma once
#include "Object3D.h"
#include "Input.h"

enum class Posture
{
	Upright,
	Croching
};

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

	/// <summary>
	/// �L�[���Z�b�g
	/// </summary>
	/// <param name="input">�L�[���</param>
	/// <returns></returns>
	Input* SetInput(Input* input) { return this->input = input; }
private:
	//���E�ړ�
	void Move();
	//�W�����v
	void Jamp();
	//�p���ύX
	void ChangePosture();
	//�d��
	void Gravity();
private:
	Input* input = nullptr;
	Posture posture = Posture::Upright;
private:
	//�d�͉��Z��
	float yadd = 0.0f;
	//���a
	float radius = 0.6f;
	//�ړ����x
	float moveSpeed = 0.4f;

	//�t���O,�^�C�}�[
	//�W�����v�t���O
	bool isJamp = false;
};

