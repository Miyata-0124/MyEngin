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
	/// <param name="sceneNum_"></param>
	/// <param name="isBlackOut_"></param>
	void Update(int sceneNum_,bool isBlackOut_);
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	//�V�[���؂�ւ��Ɏg�p������
	int GetScene() { return sceneNum; }
private:
	Sprite* sprite;
private:
	//�^�C�g���Ȃǂ�UI���
	int sceneNum = 0;

	//�g�k�t���O
	//�Ó]
	float min = 0.0f;
	float max = 1.0f;
	bool isBlackOut = false;
	float minalpha = 0.0f;
	float maxalpha = 1.0f;
};

