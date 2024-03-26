#pragma once
#include "header/2D/Sprite.h"

class AP
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

	int SetAP(int ap_) { return nowAP = ap_; }
private:
	Sprite* ap[2];
	Sprite* apBack;

private:
	int nowAP;
};

