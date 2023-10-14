#pragma once
#include "header/3D/Object3D.h"
#include "Player.h"

enum class EnemyPosture //�p���Ǘ�
{
	Wait,
	Serch,
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
	void SetPPosition(XMFLOAT3 position_) { this->playerPosition = position_; }
private:
	EnemyPosture posture = EnemyPosture::Wait;
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

