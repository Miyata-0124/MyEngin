#pragma once
#include "header/2D/Sprite.h"
/**
 * @file BlackOut.h
 * @brief シーン遷移の暗転
 * @author ミヤタ_コウキ
 * @date 2023/10/23
 */

class BlackOut
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
	Sprite* blackOut;
private:
	//拡縮フラグ
	//暗転
	float minAlpha = 0.0f;
	float maxAlpha = 1.0f;
};

