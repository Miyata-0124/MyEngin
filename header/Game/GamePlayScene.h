#pragma once
#include "header/Collider/CollisionManager.h"
#include "header/Game/GameBaseScene.h"
#include "header/3D/JsonLoader.h"
#include "header/2D/Sprite.h"

class GamePlayScene : public GameBaseScene
{
public:// メンバ変数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(ViewProjection* camera_, Input* input_) override;

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize()override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

	//マップ読み込み
	void LoadMap();
private:
	ViewProjection* camera;
	Input* input;
private:
	//スプライト機能
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	DirectXCommon* directXCom = DirectXCommon::GetInstance();

	//判定マネージャー
	CollisionManager* collisionManager = CollisionManager::GetInstance();
	//ゲーム内オブジェクト

	//パーティクル

	//マップ用JsonLoader
	//JSON
	LevelData* jsonLoader = nullptr;
	std::map<std::string, Model*> models;
	std::vector<Object3d*> objects;
};

