#pragma once
#include "header/Collider/CollisionManager.h"

#include "header/Game/BackGround.h"
#include "header/Game/BlackOut.h"
#include "header/Game/ClearSprite.h"
#include "header/Game/OverSprite.h"

class Player;
class BackGround;
class Floor;
class Item;
class Wall;
class Enemy;
class Rain;
class Gate;
class StageGate;
class ClearBox;

class GamePlayScene
{
public:// メンバ変数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(ViewProjection* camera_ , Input* input_);

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
	//スプライト機能
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	DirectXCommon* directXCom = DirectXCommon::GetInstance();
	
	ClearSprite* clearSprite = new ClearSprite();
	OverSprite* overSprite = new OverSprite();
	BlackOut* blackOut = new BlackOut();
	//判定マネージャー
	CollisionManager* collisionManager = CollisionManager::GetInstance();
	//ゲーム内オブジェクト
	//プレイヤー
	Player* objPlayer = nullptr;
	//敵
	Enemy* objEnem = nullptr;
	//床(仮)
	Floor* objFloor = nullptr;
	//アイテム
	Item* objItem = nullptr;
	//壁
	Wall* objWall = nullptr;
	//ゴールゲート
	Gate* objGoalGate[2] = {};
	StageGate* objGate = nullptr;
	ClearBox* objClearBox = nullptr;
	//背景
	BackGround* objBackGround = nullptr;
	//パーティクル
	Rain* rain = nullptr;

};

