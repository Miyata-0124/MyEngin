#pragma once
#include "header/2D/Sprite.h"
/**
 * @file BlackOut.h
 * @brief シーン遷移の暗転
 * @author ミヤタ_コウキ
 * @date 2023/10/23
 */

class BlackOut
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
	void Update(int sceneNum_,bool isBlackOut_);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//シーン切り替えに使用する情報
	int GetScene() { return sceneNum; }
private:
	Sprite* sprite;
private:
	//タイトルなどのUI情報
	int sceneNum = 0;

	//拡縮フラグ
	//暗転
	float min = 0.0f;
	float max = 1.0f;
	bool isBlackOut = false;
	float minalpha = 0.0f;
	float maxalpha = 1.0f;
};

