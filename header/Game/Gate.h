#pragma once
#include "header/3D/Object3D.h"

class Gate : public Object3d
{
public:
	/// <summary>
	/// オブジェクト生成
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static Gate* Create(Model* model = nullptr);

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

	void SetIsGoal(bool isGoal_) { isGoal = isGoal_; }
private:
	//半径
	DirectX::XMFLOAT2 radius = { 1.0f,1.0f };
	bool isGoal = false;

	//イージング用
	float min = 0.0f;
	float max = 1.0f;
	float startY = 0.0f;
	float endY = 0.0f;
	float y;
};