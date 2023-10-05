#pragma once
#include "header/3D/Object3D.h"
#include "header/Engin/Input.h"

enum class Posture //�p���Ǘ�
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
	/// <summary>
	/// �͂񂯂���n���Ă���
	/// </summary>
	/// <returns></returns>
	float GetRadius() { return radius; }
	//���W�󂯓n��
	XMFLOAT3 GetPosition() { return position; }
	//���݂̎p���󂯓n��
	Posture GetPosture() { return posture; }
	//�t���O�̎󂯓n��
	bool GetRetention() { return isRetention; }
	bool GetThrow() { return isThrow; }
	bool GetDirection() { return isDirection; }
private:
	//���E�ړ�
	void Move();
	//�W�����v
	void Jump();
	//�n�C�W�����v
	void HiJump();
	//�p���ύX
	void ChangePosture();
	//�d��
	void Gravity();
	//�A�C�e���ɑ΂���s��
	void Retention();
private:
	Input* input = nullptr;
	Posture posture = Posture::Upright;
private:
	//�d�͉��Z��
	float yadd = 0.0f;
	//���a
	float radius = 1.0f;
	//�ړ����x
	float moveSpeed = 0.4f;

	//�t���O,�^�C�}�[( false=�E , true=��)
	bool isDirection = false;
	//�W�����v
	bool isJamp = false;
	//���Ƀn�C�W�����v
	float hiJumpTimer = 5.0f;
	//�A�C�e����ێ�
	bool isRetention = false;
	//�����t���O
	bool isThrow = false;

};