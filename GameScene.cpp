#include "GameScene.h"
//#include "Affine.h"

void GameScene::Initialize() {
	//コンソールへの文字出力
	/*コンソール・・・広義でパソコン全般の入力・出力用の装置のことを指し、主にキーボードやディスプレイのこと*/
	//OutputDebugStringA("Hello,DirectX!!\n");

	//WindowsAPIの初期化
	winApp = new WinApp();
	winApp->Initialize();

	//DirectX初期化処理 ここから
	/*DirectX・・・マイクロソフトが開発したゲーム・マルチメディア処理用のAPIの集合*/
	/*API・・・Application Programming Interfaceの略
	ソフトウェアからOSの機能を利用するための仕様またはインターフェース(両者の間で情報や信号などをやりとりするための手順や規約を定めたもの)の総称
	アプリケーションの開発を容易にするためのソフトウェア資源のことをいう*/
	//HRESULT result;

	//DirectXの初期化
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//入力の初期化
	input = new Input();
	input->Initialize(winApp);

	//3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	//描画初期化ここから

	//カメラの初期化
	Object3d::SetEye({ 15.0f,20.0f,-20.0f });
	Object3d::SetTarget({ 0, 0, 0 });

	//スプライト共通部の初期化
	spriteCommon = new SpriteCommon();
	spriteCommon->Initialize(dxCommon);

	//テクスチャ読み込み
	spriteCommon->LoadTexture(1, "reimu.png");
	spriteCommon->LoadTexture(0, "test.png");

	sprite->Initialize(spriteCommon);
	sprite1->Initialize(spriteCommon);

	stageObject = Object3d::Create();
	//object3d2 = Object3d::Create();
	model = Model::LoadFromOBJ("wall");
	//model2 = Model::LoadFromOBJ("triangle_mat");
	//オブジェクトにモデルをひもづける
	stageObject->SetModel(model);
	//object3d2->SetModel(model2);

	stageObject->SetScale({ 10.0f,10.0f,10.0f });

	//viewProjection_.eye  { 0.0f,0.0f,-50.0f };
	//viewProjection_.UpdateView();
	//Affine::CreateAffine(worldTransform_);
	stageObject->Update();

	//worldTransform_.UpdateMatWorld();
	//worldTransform_.Initialize();
	//worldTransform_.scale_ = { 7.0f,7.0f,7.0f };
	//worldTransform_.translation_ = { 0.0f,0.0f,0.0f };
	//Affine::CreateAffine(worldTransform_);

	//worldTransform_.UpdateMatWorld();
}

void GameScene::Finalize() {
	//WindowsAPIの終了処理
	winApp->Finalize();

	//スプライト解放
	delete sprite;
	delete sprite1;
	delete spriteCommon;
	//3Dオブジェクト解放
	delete stageObject;
	//delete object3d2;
	//3Dモデル解放
	delete model;
	delete model2;
	//DirectX解放
	delete dxCommon;
	//入力解放
	delete input;
	//WindowsAPI解放
	delete winApp;

}

void GameScene::Update() {


	//DirectX毎フレーム処理 ここから

	//入力の更新
	input->Update();
	sprite->Update(spriteCommon);
}

void GameScene::Draw() {
	//描画前処理
	dxCommon->PreDraw();

	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());

	//3Dオブジェクトの描画
	stageObject->Draw();
	//object3d2->Draw();
	//3Dオブジェクト描画後処理
	Object3d::PostDraw();

	//スプライト描画前処理
	spriteCommon->PreDraw();

	////描画コマンドここから
	spriteCommon->Update(dxCommon);
	//sprite->SetPosition(position);
	sprite1->SetPosition({ 100.0f,100.0f });
	sprite->SetIndex(0);
	sprite1->SetIndex(1);
	//sprite1->SetTextureSize({ 500.0f,450.0f });

	//sprite->Draw(spriteCommon);
	//sprite1->Draw(spriteCommon);
	////描画コマンドここまで

	//スプライト描画後処理
	spriteCommon->PostDraw();


	dxCommon->PostDraw();


	//DirectX毎フレーム処理 ここまで
}