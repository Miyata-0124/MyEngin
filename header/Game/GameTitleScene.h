#pragma once
#include "header/Engin/ViewProjection.h"
#include "header/Game/BlackOut.h"
#include "header/Game/TitleSprite.h"

class Rain;

class GameTitleScene
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(ViewProjection* camera_,Input* input_);

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
private:
	Input* input = nullptr;
	//スプライト機能
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	DirectXCommon* directXCom = DirectXCommon::GetInstance();

	//ゲーム内スプライト
	TitleSprite* titleSprite = new TitleSprite();
	//暗転
	BlackOut* blackOut = new BlackOut();
	//パーティクル
	Rain* rain = nullptr;

private:
	//スプライトの落下地点
	float landingPoint = 720;
};

