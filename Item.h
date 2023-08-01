#pragma once
#include "Input.h"
#include "Object3D.h"
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

	void SetRetention(bool isRetention) { this->isRetention = isRetention; }
	//�v���C���[�̍��W�擾
	void SetPPosition(XMFLOAT3 position) { this->playerPosition = position; }
	//�v���C���[�̌����擾
	void SetDirection(bool isDirection) { this->isDirection = isDirection; }

	/// <summary>
	/// �L�[���Z�b�g
	/// </summary>
	/// <param name="input">�L�[���</param>
	/// <returns></returns>
	Input* SetInput(Input* input) { return this->input = input; }

private:
	void Gravity();

private:
	//�d�͉��Z��
	float yadd = 0.0f;
	//���a
	float radius = 1.0f;
	//�ړ����鑬�x
	float throwSpeed = 3.0f;

	//�^�C�}�[,�t���O
	bool isRetention = false;
	bool isThrow = false;
	bool isDirection = false;

	float throwTimer = 3.0f; //�|����������

	XMFLOAT3 playerPosition;
private:
	Input* input = nullptr;

};