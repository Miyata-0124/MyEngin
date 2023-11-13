#pragma once
#include "header/2D/Sprite.h"
#include "header/Engin/Input.h"

class ClearSprite
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
	/// <param name="sceneNum_"></param>
	/// <param name="isBlackOut_"></param>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	void Reset();
private:
	Sprite* clearSprite;
private:
	bool isBlackOut = false;
	//�Q�[���I�[�o�[���~���Ă���^�C�}�[
	float downTimer = 0.0f;
	//�C�[�W���O�p
	float min = 0.0f;
	float max = 1.0f;
	float startY = 0.0f;
	float endY = 100.0f;
	float y;
	//�A���t�@�l
	bool isAlpha = false;
	float alphaTimer = 0.0f;
	float alpha = 0.0f;
	int alphaCount = 0;

};