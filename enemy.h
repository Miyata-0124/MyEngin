#pragma once
#include "Object3D.h"

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
	EnemyPosture posture = EnemyPosture::Wait;
	int ChengeTimer = 50;
	//���a
	float radius = 1.0f;

	float speed = 0.5f;
};

