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

	//ゲートナンバーの設定
	void SetGateNum(int32_t gateNum_) { this->gateNum = gateNum_; }
	void SetIsGoal(bool isGoal_) { this->isGoal = isGoal_; }

	bool GetIsGoal() { return isGoal; }
private:
	int32_t gateNum;

	XMFLOAT3 position_[2];
	//半径
	DirectX::XMFLOAT2 radius = { 1.0f,1.0f };

	bool isGoal = false;
	//イージング用
	float min = 0.0f;
	float max = 1.0f;
	float startY[2] = { -40.0f,40.0f };
	float endY = 0.0f;
	float y;
};