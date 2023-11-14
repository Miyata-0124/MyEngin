#pragma once
#include "header/Game/GameBaseScene.h"

class GameSceneManager
{
public: 
	/// <summary>
	/// 更新
	/// </summary>
	void  Update(ViewProjection* camera_,Input* input_);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
public:
	//デストラクタ
	~GameSceneManager();

	//シーンの予約
	void SetNextScene(GameBaseScene* nextScene_) { nextScene = nextScene_; }
private:
	//実行中のシーン
	GameBaseScene* scene = nullptr;
	//次のシーン
	GameBaseScene* nextScene = nullptr;
};

