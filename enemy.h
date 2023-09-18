#pragma once
#include "Object3D.h"

enum class EnemyPosture //姿勢管理
{
	Wait,
	Move
};

class Enemy : public Object3d
{
public:
	/// <summary>
	/// オブジェクト生成
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static Enemy* Create(Model* model = nullptr);

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns></returns>
	bool Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// コールバック
	/// </summary>
	/// <param name="info"></param>
	void OnCollider(const CollisionInfo& info)override;

private:
	EnemyPosture posture = EnemyPosture::Wait;
	int ChengeTimer = 50;
	//半径
	float radius = 1.0f;

	float speed = 0.5f;
};

