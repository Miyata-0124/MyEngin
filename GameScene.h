#pragma once
//自作クラス
#include <list>
#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "ViewProjection.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Particle.h"
#include "Object3d.h"
#include "FbxObject3D.h"
#include "FbxLoader.h"
#include "Model.h"
#include "JsonLoader.h"
#include "BackGround.h"

class CollisionManager;
class Player;
class BackGround;
class Floor;
class Item;
class Wall;
class Enemy;

class GameScene
{
public: //基本関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 解放
	/// </summary>
	void Finalize();

	void LoadMap();

public: //mainに一部引き渡し用
	WinApp* GetWinApp() { return winApp; }
	Input* GetInput() { return input; }

private: //ゲーム内使用クラス
	WinApp* winApp = nullptr;
	DirectXCommon* directXCom = nullptr;
	//デバッグテキスト
	//ImguiManager* imgui = nullptr;
	//キー情報
	Input* input = nullptr;
	//カメラ
	ViewProjection* camera = nullptr;
	//スプライト
	SpriteCommon* spriteCommon = nullptr;
	Sprite* sprite = new Sprite();
	//FBX
	FbxModel* model = nullptr;
	FbxObject3d* object1 = new FbxObject3d();
	
	//マップ用JsonLoader
	//JSON
	LevelData* jsonLoader = nullptr;
	std::map<std::string, Model*> models;
	std::vector<Object3d*> objects;

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
	//背景
	BackGround* objBackGround = nullptr;

	CollisionManager* collisionManager = nullptr;

	//パーティクル
	Particle* particle = nullptr;
	//シーン切り替え要情報
	int scene = 0;
	//タイトルなどのUI情報
	bool ChengeScene = false;
	//タイトルの文字を動かす変数
	XMFLOAT2 UIspeed = { 0,0 };
	//もじをどちらに動かすか確認するフラグ
	bool UIFlag = false;;
};

