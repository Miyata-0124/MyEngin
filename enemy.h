#pragma once
#include "Object3D.h"
#include "Player.h"

enum class EnemyPosture //�p���Ǘ�
{
	Wait,
	Move
};

class Enemy : public Object3d
{
public:
	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static Enemy* Create(Model* model = nullptr);

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
	void Gravity();

public:
	//�v���C���[�̍��W�擾
	void SetPPosition(XMFLOAT3 position) { this->playerPosition = position; }
private:
	EnemyPosture posture = EnemyPosture::Wait;
	int ChengeTimer = 50;
	//���a
	float radius = 1.0f;
	//�ړ����x
	float speed = 0.0f;
	//�d�͉��Z��
	float yadd = 0.0f;

	//�ړ���
	float move = 0.0f;

	XMFLOAT3 playerPosition;
};

