#pragma once
#include "header/3D/Object3D.h"
#include "Player.h"

enum class EnemyPosture //姿勢管理
{
	Wait,
	Serch,
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
	void SetPPosition(XMFLOAT3 position_) { this->playerPosition = position_; }
private:
	EnemyPosture posture = EnemyPosture::Wait;
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

