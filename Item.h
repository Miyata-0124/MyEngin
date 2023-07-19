#pragma once
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

private:
	void Gravity();

private:
	//重力加算量
	float yadd = 0.0f;
	//半径
	float radius = 0.5f;

	//タイマー,フラグ
};