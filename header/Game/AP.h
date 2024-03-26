#pragma once
#include "header/2D/Sprite.h"

class AP
{
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	/// <param name="spriteCommon"></param>
	void Initialize(SpriteCommon* spriteCommon);
	/// <summary>
	/// XV
	/// </summary>
	/// <param name="sceneNum_"></param>
	/// <param name="isBlackOut_"></param>
	void Update();
	/// <summary>
	/// •`‰æ
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

