#pragma once
#include "header/Collider/CollisionManager.h"

#include "header/Game/GameBaseScene.h"
#include "header/Game/BackGround.h"
#include "header/Game/BlackOut.h"
#include "header/Game/WakeUp.h"
#include "header/3D/JsonLoader.h"

class Player;
class BackGround;
class Platform;
class Pipe;
class Item;
class Floor;
class Wall;
class Enemy;
class Rain;
class MoveGate;
class Gate;
class ClearBox;

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
	//スプライト
	//演出
	std::unique_ptr<WakeUp> wakeUp = nullptr;
	//暗転
	std::unique_ptr<BlackOut> blackOut = nullptr;
	std::unique_ptr<Sprite> back = nullptr;
	//判定マネージャー
	CollisionManager* collisionManager = CollisionManager::GetInstance();
	//ゲーム内オブジェクト
	//プレイヤー
	Player* objPlayer = nullptr;
	//敵
	Enemy* objEnem = nullptr;
	//床(仮)
	Platform* objFloor = nullptr;
	//パイプ
	Pipe* objPipe = nullptr;
	//壁
	Floor* objWall = nullptr;
	//プレイヤーを通さない壁
	Wall* objKeepsWall = nullptr;
	//アイテム
	Item* objItem = nullptr;
	//クリア判定用箱
	ClearBox* objClearBox = nullptr;
	//マップ移動用ゲート
	MoveGate* objMGate = nullptr;
	//扉
	Gate* objGate = {};
	//背景
	BackGround* objBackGround = nullptr;
	//パーティクル
	//Rain* rain = nullptr;

	bool move = false;

	//マップ用JsonLoader
	//JSON
	LevelData* jsonLoader = nullptr;
	std::map<std::string, Model*> models;
	std::vector<Object3d*> objects;
};

