/**
 * @file GameScene.h
 * @brief ゲーム関連の基盤 ここに書き込んでいく
 * @author ミヤタ_コウキ
 * @date 2022/04/13
 */

#pragma once
//自作クラス
#include <list>
#include "header/Engin/Input.h"
#include "header/Engin/WinApp.h"
#include "header//Engin/DirectXCommon.h"
#include "header/Engin/ViewProjection.h"
#include "header/2D/SpriteCommon.h"
#include "header/3D/Object3D.h"
#include "header/3D/FbxObject3D.h"
#include "header/3D/FbxModel.h"
#include "header/3D/Model.h"
#include "header/3D/JsonLoader.h"
//シーン関連
#include "header/Game/GameSceneManager.h"
#include "header/Game/GameTitleScene.h"
#include "header/Game/GamePlayScene.h"

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
	DirectXCommon* directXCom = DirectXCommon::GetInstance();
	//デバッグテキスト
	//ImguiManager* imgui = nullptr;
	//キー情報
	Input* input = nullptr;
	//カメラ
	ViewProjection* camera = nullptr;
	
	//FBX
	FbxModel* model = nullptr;
	FbxObject3d* object1 = new FbxObject3d();
	
	//シーンマネージャ
	GameSceneManager* sceneManager = nullptr;
	//マップ用JsonLoader
	//JSON
	LevelData* jsonLoader = nullptr;
	std::map<std::string, Model*> models;
	std::vector<Object3d*> objects;


	//シーン切り替え要情報
	int scene = 0;
	//雨を管理する時計
	float rainTimer = 0.0f;
	bool rainFlag = false;
	////UI関連
	bool isBlackOut = false;

	GameBaseScene* scene_ = nullptr;
};

