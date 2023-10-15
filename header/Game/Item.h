/**
 * @file Item.h
 * @brief �v���C���[�������^�яo����I�u�W�F�N�g�N���X
 * @author �~���^_�R�E�L
 * @date 2023/07/27
 */

#pragma once
#include "header/Engin/Input.h"
#include "header/3D/Object3D.h"
/// <summary>
/// �����o����A�C�e��(�΂⑄�Ȃ�)
/// </summary>

class Item : public Object3d
{
public:
	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static Item* Create(Model* model = nullptr);

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

	void RetentionThrow();

	float GetRadius() { return radius; }

	void SetRetention(bool isRetention_) { this->isRetention = isRetention_; }
	//�v���C���[�̍��W�擾
	void SetPPosition(XMFLOAT3 position_) { this->playerPosition = position_; }
	//�v���C���[�̌����擾
	void SetDirection(bool isDirection_) { this->isDirection = isDirection_; }

	/// <summary>
	/// �L�[���Z�b�g
	/// </summary>
	/// <param name="input">�L�[���</param>
	/// <returns></returns>
	Input* SetInput(Input* input_) { return this->input = input_; }

private:
	void Gravity();
	void ThrowLength();
private:
	//�d�͉��Z��
	float yadd = 0.0f;
	float g = 0.80f;
	//���a
	float radius = 1.0f;
	//�ړ����鏉���x
	float throwSpeed = 1.25f;
	//����
	double height;
	//���B�_
	double length;

	//�^�C�}�[,�t���O
	bool isRetention = false;
	bool isThrow = false;
	bool isDirection = false;

	float throwTimer = 3.0f; //�|����������

	XMFLOAT3 playerPosition;
private:
	Input* input = nullptr;

};