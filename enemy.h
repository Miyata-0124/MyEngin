#pragma once
#include "Object3D.h"
#include "Player.h"

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
	void Gravity();

public:
	//プレイヤーの座標取得
	void SetPPosition(XMFLOAT3 position) { this->playerPosition = position; }
private:
	EnemyPosture posture = EnemyPosture::Wait;
	int ChengeTimer = 50;
	//半径
	float radius = 1.0f;
	//移動速度
	float speed = 0.0f;
	//重力加算量
	float yadd = 0.0f;

	//移動量
	float move = 0.0f;

	XMFLOAT3 playerPosition;
};

