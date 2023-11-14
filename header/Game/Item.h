/**
 * @file Item.h
 * @brief プレイヤーが持ち運び出来るオブジェクトクラス
 * @author ミヤタ_コウキ
 * @date 2023/07/27
 */

#pragma once
#include "header/Engin/Input.h"
#include "header/3D/Object3D.h"
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

	void SetRetention(bool isRetention_) { this->isRetention = isRetention_; }
	//プレイヤーの座標取得
	void SetPPosition(XMFLOAT3 position_) { this->playerPosition = position_; }
	//プレイヤーの向き取得
	void SetDirection(bool isDirection_) { this->isDirection = isDirection_; }

	/// <summary>
	/// キー情報セット
	/// </summary>
	/// <param name="input">キー情報</param>
	/// <returns></returns>
	Input* SetInput(Input* input_) { return this->input = input_; }

private:
	void Gravity();
	void ThrowLength();
private:
	//重力加算量
	float yadd = 0.0f;
	float g = 0.80f;
	//半径
	float radius = 1.0f;
	//移動する初速度
	float throwSpeed = 1.25f;
	//高さ
	double height;
	//到達点
	double length;

	//タイマー,フラグ
	bool isRetention = false;
	bool isThrow = false;
	bool isDirection = false;

	float throwTimer = 3.0f; //掛かった時間

	XMFLOAT3 playerPosition;
private:
	Input* input = nullptr;

};