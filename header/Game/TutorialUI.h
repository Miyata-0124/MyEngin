#pragma once
#include "header/2D/Sprite.h"

class TutorialUI
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

	float SetPlayerPos(float playerPos_) { return playerPos = playerPos_; }
private:
	Sprite* tutorialUI[4];

	float playerPos;
};

