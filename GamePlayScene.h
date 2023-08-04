#pragma once
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Floor.h"
#include "Item.h"
#include "BackGround.h"
#include <sstream>
#include <iomanip>

class GamePlayScene
{
public:
	// 初期化
	void Initialize();

	// 終了
	void Finalize();

	// 更新
	void Update();

	//描画
	void Draw();

private:
	//プレイヤー
	Player* objPlayer = nullptr;
	//床(仮)
	Floor* objFloor = nullptr;
	//アイテム
	Item* objItem = nullptr;
	//背景
	BackGround* objBackGround = nullptr;

	CollisionManager* collisionManager = nullptr;
};

