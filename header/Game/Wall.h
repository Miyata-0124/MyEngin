/**
 * @file Wall.h
 * @brief 壁の機能
 * @author ミヤタ_コウキ
 * @date 2023/10/10
 */

#pragma once
#include "header/3D/Object3D.h"

class Floor : public Object3d
{
public:
	/// <summary>
	/// オブジェクト生成
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static Floor* Create(Model* model = nullptr);

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

	//ゲッター,セッター
private:

};

