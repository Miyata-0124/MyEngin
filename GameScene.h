#pragma once
//自作クラス
#include <list>
#include "Input.h"
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
#include "Framework.h"

class CollisionManager;
class Player;
class BackGround;
class Floor;
class Item;

class GameScene : public Framework
{
public: //基本関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 解放
	/// </summary>
	void Finalize() override;

	void LoadMap();

public: //mainに一部引き渡し用
	Input* GetInput() { return input; }

private: //ゲーム内使用クラス
	
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
	//床(仮)
	Floor* objFloor = nullptr;
	//アイテム
	Item* objItem = nullptr;
	//背景
	BackGround* objBackGround = nullptr;

	CollisionManager* collisionManager = nullptr;
};

