#pragma once
#include "header/2D/Sprite.h"
#include "header/Engin/Input.h"

class ClearSprite
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
	/// <param name="sceneNum_"></param>
	/// <param name="isBlackOut_"></param>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void Reset();
private:
	Sprite* clearSprite;
private:
	bool isBlackOut = false;
	//ゲームオーバーが降ってくるタイマー
	float downTimer = 0.0f;
	//イージング用
	float min = 0.0f;
	float max = 1.0f;
	float startY = 0.0f;
	float endY = 100.0f;
	float y;
	//アルファ値
	bool isAlpha = false;
	float alphaTimer = 0.0f;
	float alpha = 0.0f;
	int alphaCount = 0;

};