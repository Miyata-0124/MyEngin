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

//	switch (scene)
//	{
//	case 0: //タイトル画面 雨が降っているように見えるタイトル
////#pragma region パーティクル
////		rain->Update();
////#pragma endregion
////#pragma region シーン切り替え時の処理
////
////
////		titleSprite->Update(input, scene, isBlackOut);
////		isBlackOut = titleSprite->GetBlackOut();
////
////		//暗転させるのか判断
////		blackOut->Update(scene, isBlackOut);//暗転後シーン切り替えをする
////		scene = blackOut->GetScene();//切り替えた情報を渡す->切り替わる
//
//#pragma endregion
//		break;
//	case 1:
//		
//
//		break;
//	case 2:
//		/*rain->Update();
//		overSprite->Update();*/
//		break;
//	}

}

void GameScene::Draw()
{
	//描画処理ここから↓
	directXCom->PreDraw();

	sceneManager->Draw();

	directXCom->PostDraw();
	//ここまで↑

	//switch (scene)
	//{
	//case 0:
	//	
	//	//タイトル
	//	//titleSprite->Draw();

	//	//rain->Draw();
	//	////暗転用
	//	//blackOut->Draw();
	//	break;

	//case 1:

	//	break;
	//case 2:
	//	/*rain->Draw();
	//	overSprite->Draw();*/
	//	break;
	//}


}

void GameScene::Finalize()
{
	winApp->Finalize();
	sceneManager->~GameSceneManager();
	FbxLoader::GetInstance()->Finalize();
	delete input;
	delete winApp;
	delete model;
	
	//scene_->Finalize();
	//delete scene_;
	//delete object1;
	/*delete model1;
	delete obj3d;*/
}

//void GameScene::LoadMap()
//{
//	for (auto& objectData : jsonLoader->objects) {
//		Model* model_ = Model::LoadFromOBJ("TestBox");
//		decltype(models)::iterator it = models.find(objectData.fileName);
//		if (it != models.end()) { model_ = it->second; }
//
//		// モデルを指定して3Dオブジェクトを生成
//		Object3d* mapObject = Object3d::Create();
//		mapObject->SetModel(model_);
//		// 座標
//		DirectX::XMFLOAT3 scale;
//		DirectX::XMStoreFloat3(&scale, objectData.scaling);
//		mapObject->SetSize(scale);
//
//		// 回転角
//		DirectX::XMFLOAT3 rot;
//		DirectX::XMStoreFloat3(&rot, objectData.rotation);
//		mapObject->SetRotation(rot);
//
//		// 座標
//		DirectX::XMFLOAT3 pos;
//		DirectX::XMStoreFloat3(&pos, objectData.position);
//		mapObject->SetPosition(pos);
//
//		//コライダー
//		DirectX::XMFLOAT3 center;
//		DirectX::XMFLOAT2 radius;
//		DirectX::XMStoreFloat3(&center, objectData.center);
//		DirectX::XMStoreFloat2(&radius, objectData.size);
//
//		mapObject->SetCollider(new BoxCollider({ center.x,center.y+radius.y/2,center.z }, { radius.x/2,radius.y/2 }));
//		// 配列に登録
//		objects.push_back(mapObject);
//	}
//}
