#pragma once
#include "header/Collider/CollisionManager.h"

#include "header/Engin/ViewProjection.h"
#include "header/Game/GameBaseScene.h"

#include "header/Game/BlackOut.h"
#include "header/Game/ClearSprite.h"

#include "header/3D/JsonLoader.h"

class Player;
class Platform;
class Gate;
class ClearBox;
class Rain;
class Floor;

class GameClearScene : public GameBaseScene
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(ViewProjection* camera_, Input* input_)override;

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
	ViewProjection* camera = nullptr;
	Input* input = nullptr;
	//スプライト機能
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	DirectXCommon* directXCom = DirectXCommon::GetInstance();
	//暗転
	BlackOut* blackOut = new BlackOut();
	ClearSprite* clearSprite = new ClearSprite();
	//判定マネージャー
	CollisionManager* collisionManager = CollisionManager::GetInstance();
	//オブジェクト
	//プレイヤー
	Player* objPlayer = nullptr;
	//壁
	Floor* objWall = {};
	//扉
	Gate* objGate = {};
	//クリア判定用箱
	ClearBox* objClearBox = nullptr;

	//パーティクル
	Rain* rain = nullptr;

	//マップ用JsonLoader
	//JSON
	LevelData* jsonLoader = nullptr;
	std::map<std::string, Model*> models;
	std::vector<Object3d*> objects;
};

