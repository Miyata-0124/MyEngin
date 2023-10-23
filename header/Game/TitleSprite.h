#pragma once
#include "header/2D/Sprite.h"
#include "header/Engin/Input.h"
/**
 * @file BlackOut.h
 * @brief タイトルのスプライト
 * @author ミヤタ_コウキ
 * @date 2023/10/23
 */

class TitleSprite
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
	void Update(Input* input,int sceneNum_, bool isBlackOut_);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//シーン切り替えに使用する情報
	bool GetBlackOut() { return isBlackOut; }
private:
	Sprite* titleSprite;
private:
	//タイトルなどのUI情報
	bool ChengeScene = false;
	//UI関連
	bool UIFlag = false;
	DirectX::XMFLOAT2 UIspeed = { 0,0 };

	int sceneNum = 0;
	//拡縮フラグ
	//暗転
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

