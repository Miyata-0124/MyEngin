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
#include "Item.h"
#include "Floor.h"
#include "ImGuiManager.h"
#include "JsonLoader.h"

class CollisionManager;
class Player;

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
	ImguiManager* imgui = nullptr;;
	//キー情報
	Input* input = nullptr;
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
	//床(仮)
	Floor* objFloor = nullptr;
	//アイテム
	Item* objItem = nullptr;

	CollisionManager* collisionManager = nullptr;
};

