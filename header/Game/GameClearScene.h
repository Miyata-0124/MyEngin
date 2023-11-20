#pragma once
#include "header/Collider/CollisionManager.h"

#include "header/Engin/ViewProjection.h"
#include "header/Game/GameBaseScene.h"

#include "header/Game/BlackOut.h"

class Player;
class Floor;
class Gate;
class ClearBox;

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
private:
	ViewProjection* camera = nullptr;
	Input* input = nullptr;
	//スプライト機能
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	DirectXCommon* directXCom = DirectXCommon::GetInstance();
	//暗転
	BlackOut* blackOut = new BlackOut();
	//判定マネージャー
	CollisionManager* collisionManager = CollisionManager::GetInstance();
	//オブジェクト
	//プレイヤー
	Player* objPlayer = nullptr;
	//床(仮)
	Floor* objFloor[3] = {};
	//扉
	Gate* objGate[2] = {};
	//クリア判定用箱
	ClearBox* objClearBox = nullptr;
};

