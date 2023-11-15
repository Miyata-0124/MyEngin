#pragma once
#include "header/2D/Particle.h"

class Rain : public Particle
{
public:
	/// <summary>
	/// オブジェクト生成
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static Rain* Create();
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns></returns>
	bool Initialize(uint32_t texIndex_) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

private:
	//雨を管理する時計
	float rainTimer = 0.0f;
	bool rainFlag = false;
	//テクスチャのインデックス
	static const uint32_t texIndex = 1;
};

