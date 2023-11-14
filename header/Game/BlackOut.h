#pragma once
#include "header/2D/Sprite.h"
/**
 * @file BlackOut.h
 * @brief �V�[���J�ڂ̈Ó]
 * @author �~���^_�R�E�L
 * @date 2023/10/23
 */

class BlackOut
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
	Sprite* blackOut;
private:
	//�g�k�t���O
	//�Ó]
	float minAlpha = 0.0f;
	float maxAlpha = 1.0f;
};

