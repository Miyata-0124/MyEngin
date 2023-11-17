#pragma once
#include "header/2D/Sprite.h"
enum class Blink
{
	slowOpen,
	slowClose,
	Open,
};

class WakeUp
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="spriteCommon"></param>
	void Initialize(SpriteCommon* spriteCommon);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	//リセット
	void Reset();

	//アルファ値
	float GetMinAlpha() { return minAlpha; }
	float GetMaxAlpha() { return maxAlpha; }
private:
	Sprite* wakeUp;
	Blink blink;
private:
	int blinkCount = 0;
	//拡縮フラグ
	//暗転
	float minAlpha = 1.0f;
	float maxAlpha = 0.0f;
};