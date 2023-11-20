#pragma once
#include "header/Collider/CollisionManager.h"

#include "header/Game/GameBaseScene.h"
#include "header/Game/BackGround.h"
#include "header/Game/BlackOut.h"
#include "header/Game/WakeUp.h"

class Player;
class BackGround;
class Floor;
class Item;
class Wall;
class Enemy;
class Rain;
class MoveGate;
class ClearBox;

enum class MAP
{
	MAP1,
	MAP2,
};

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

private:
	ViewProjection* camera;
	Input* input;

	MAP map = MAP::MAP1;
private:
	//スプライト機能
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	DirectXCommon* directXCom = DirectXCommon::GetInstance();
	//スプライト
	//演出
	WakeUp* wakeUp = new WakeUp();
	//暗転
	BlackOut* blackOut = new BlackOut();

	Sprite* sprite[3] = { new Sprite(),new Sprite, new Sprite };
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
	//マップ移動用ゲート
	MoveGate* objGate = nullptr;
	//背景
	BackGround* objBackGround = nullptr;
	//パーティクル
	Rain* rain = nullptr;

	XMFLOAT3 move = { 0,0,0 };
};

