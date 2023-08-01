#pragma once
#include "Input.h"
#include "Object3D.h"
/// <summary>
/// 投擲出来るアイテム(石や槍など)
/// </summary>

class Item : public Object3d
{
public:
	/// <summary>
	/// オブジェクト生成
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static Item* Create(Model* model = nullptr);

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

	void RetentionThrow();

	float GetRadius() { return radius; }

	void SetRetention(bool isRetention) { this->isRetention = isRetention; }
	//プレイヤーの座標取得
	void SetPPosition(XMFLOAT3 position) { this->playerPosition = position; }
	//プレイヤーの向き取得
	void SetDirection(bool isDirection) { this->isDirection = isDirection; }

	/// <summary>
	/// キー情報セット
	/// </summary>
	/// <param name="input">キー情報</param>
	/// <returns></returns>
	Input* SetInput(Input* input) { return this->input = input; }

private:
	void Gravity();

private:
	//重力加算量
	float yadd = 0.0f;
	//半径
	float radius = 1.0f;
	//移動する速度
	float throwSpeed = 3.0f;

	//タイマー,フラグ
	bool isRetention = false;
	bool isThrow = false;
	bool isDirection = false;

	float throwTimer = 3.0f; //掛かった時間

	XMFLOAT3 playerPosition;
private:
	Input* input = nullptr;

};