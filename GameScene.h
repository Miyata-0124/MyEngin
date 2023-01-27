#pragma once
#include "Object3d.h"
#include "Sprite.h"
#include "Input.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"

class GameScene
{
public:

	//初期化
	void Initialize();
	//終了
	void Finalize();
	//毎フレーム処理
	void Update();
	//描画
	void Draw();

	WinApp* GetWinApp() { return winApp; }

private:
	const float PI = 3.14159f;

	//ポインタ
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;

	//スプライト共通部のポインタ
	SpriteCommon* spriteCommon = nullptr;

	Sprite* sprite = new Sprite();
	Sprite* sprite1 = new Sprite();

	//OBJからモデルデータを読み込む
	Model* model = nullptr;
	Model* model2 = nullptr;
	//3Dオブジェクト生成
	Object3d* stageObject = nullptr;
	//Object3d* object3d2 = nullptr;
	//WorldTransform worldTransform_;
	//ViewProjection viewProjection_;
};