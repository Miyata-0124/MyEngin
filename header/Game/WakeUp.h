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
	/// ������
	/// </summary>
	/// <param name="spriteCommon"></param>
	void Initialize(SpriteCommon* spriteCommon);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	//���Z�b�g
	void Reset();

	//�A���t�@�l
	float GetMinAlpha() { return minAlpha; }
	float GetMaxAlpha() { return maxAlpha; }
private:
	Sprite* wakeUp;
	Blink blink;
private:
	int blinkCount = 0;
	//�g�k�t���O
	//�Ó]
	float minAlpha = 1.0f;
	float maxAlpha = 0.0f;
};