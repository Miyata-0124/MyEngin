#pragma once
//マップ移動判定用オブジェクト

#include "header/3D/Object3D.h"

class StageGate : public Object3d
{
public:
	/// <summary>
	/// オブジェクト生成
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static StageGate* Create(Model* model = nullptr);

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
	//半径
	DirectX::XMFLOAT2 radius = { Object3d::GetScale().x,Object3d::GetScale().y};

	//移動の初期地点
	XMVECTOR startPos = {};
	//移動後の到着店
	XMVECTOR endPos = {};
	//最小
	float min = 0.0f;
	//最大
	float max = 1.0f;
};

