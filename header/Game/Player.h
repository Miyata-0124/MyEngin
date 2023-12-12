/**
 * @file Player.h
 * @brief ����\�ȃv���C���[�I�u�W�F�N�g
 * @author �~���^_�R�E�L
 * @date 2023/06/15
 */

#pragma once
#include "header/3D/Object3D.h"
#include "header/Engin/Input.h"

enum class Posture //�p���Ǘ�
{
	Upright,	//����
	Croching,	//���Ⴊ��
	Climing
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
	Input* SetInput(Input* input_) { return this->input = input_; }

	bool SetIsStop(bool isStop_) { return this->isStop = isStop_; }
	/// <summary>
	/// ���a��n���Ă���
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
	//�V�[���؂�ւ��Ɏg�p������
	int GetScene() { return sceneNum; }

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
	//�W�����v���̔��d��
	float antiYadd = -1.5f;
	//���a
	float radius = 1.0f;
	//�ړ����x
	float moveSpeed = 0.4f;
	bool isMove = true;
	//���Ƀn�C�W�����v
	float hiJumpTimer = 5.0f;

	//�t���O,�^�C�}�[( false=�E , true=��)
	bool isDirection = false;
	//�W�����v
	bool isJamp = true;
	//�A�C�e����ێ�
	bool isRetention = false;
	//�����t���O
	bool isThrow = false;
	//�A�C�e�����h�����Ă��邩�̔���
	bool isStop = false;

	int sceneNum = 0;

	//�J�����̑��x
	float cameraSpeed = 0.0f;
};