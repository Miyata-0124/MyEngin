#pragma once
#include "header/2D/Sprite.h"
#include "header/Engin/Input.h"
/**
 * @file BlackOut.h
 * @brief �^�C�g���̃X�v���C�g
 * @author �~���^_�R�E�L
 * @date 2023/10/23
 */

class TitleSprite
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
	void Update(Input* input,int sceneNum_, bool isBlackOut_);
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	//�V�[���؂�ւ��Ɏg�p������
	bool GetBlackOut() { return isBlackOut; }
private:
	Sprite* titleSprite;
private:
	//�^�C�g���Ȃǂ�UI���
	bool ChengeScene = false;
	//UI�֘A
	bool UIFlag = false;
	DirectX::XMFLOAT2 UIspeed = { 0,0 };

	int sceneNum = 0;
	//�g�k�t���O
	//�Ó]
	float min = 0.0f;
	float max = 1.0f;
	float startY = 0.0f;
	float endY = 720.0f;
	float y;
	bool isBlackOut = false;
	float blackOutTimer = 300.0f;
	float minalpha = 0.0f;
	float maxalpha = 1.0f;
};

