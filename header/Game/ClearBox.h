#pragma once
#include "header/3D/Object3D.h"

class ClearBox : public Object3d
{
public:
	/// <summary>
	/// オブジェクト生成
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static ClearBox* Create(Model* model = nullptr);

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

	bool GetIsGoal() { return isGoal; }

private:
	//半径
	DirectX::XMFLOAT2 radius = { 10.0f,5 };

	bool isGoal = false;
};

