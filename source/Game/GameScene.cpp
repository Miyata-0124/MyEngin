#include "header/Game/GameScene.h"

#include <sstream>
#include <iomanip>



void GameScene::Initialize()
{
#pragma region WindowsAPIの初期化
	winApp = new WinApp;
	winApp->Initialize();
#pragma endregion

#pragma region DirectX初期化処理
	//DirectX初期化処理　　ここから
	directXCom->Initialize(winApp);

	//FBX関連
	FbxLoader::GetInstance()->Initialize(directXCom->GetDevice());

	//キー情報
	input = new	Input;
	input->Initialize(winApp);

	//マネージャ生成
	sceneManager = new GameSceneManager();

	//DirectX初期化処理　　ここまで
	//ViewProjection
	camera = new ViewProjection();
	camera->Initialeze();

	//タイトルシーン
	scene_ = new GameTitleScene();
	//初期シーンを設定する
	sceneManager->SetNextScene(scene_);
#pragma	endregion
	
}

void GameScene::Update()
{
	//キー情報
	input->Update();
	//カメラ
	camera->Update();

	sceneManager->Update(camera, input);
}

void GameScene::Draw()
{
	//描画処理ここから↓
	directXCom->PreDraw();

	sceneManager->Draw();

	directXCom->PostDraw();
	//ここまで↑
}

void GameScene::Finalize()
{
	winApp->Finalize();
	sceneManager->~GameSceneManager();
	FbxLoader::GetInstance()->Finalize();
	delete input;
	delete winApp;
	delete model;
	//delete scene_;
	//delete object1;
	/*delete model1;
	delete obj3d;*/
}