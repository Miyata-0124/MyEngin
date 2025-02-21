#include "header/Game/GamePlayScene.h"
#include "header/Game/GameSceneManager.h"
#include "header/3D/FbxObject3D.h"
#include "header/3D/Object3D.h"
#include "header/2D/Sprite.h"
#include "easing/Easing.h"

void GamePlayScene::Initialize(ViewProjection* camera_, Input* input_)
{
	camera = camera_;
	input = input_;

	//スプライト共通部分の初期化
	spriteCommon->Initialize(directXCom);
	//spriteCommon->Loadtexture(1, "fileName");
	
	//一度しか宣言しない
	Object3d::StaticInitialize(directXCom->GetDevice(), camera);
	FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	//Particle::StaticInitialize(directXCom->GetDevice(), camera);
	
	//json読み込み
	jsonLoader = JsonLoader::LoadFlomJSONInternal("map");
	//マップ読み込み
	LoadMap();
#pragma region FBX
	//FbxModel* playerModel = FbxLoader::GetInstance()->LoadModelFromFile("player");
	/*

	object1->initialize();
	object1->SetModel(model);
	object1->SetRotation({ 0,60,0 });
	object1->SetPosition({ 0,-3,0 });
	object1->PlayAnimation();*/
#pragma endregion
#pragma region モデル
	//モデル
#pragma endregion
#pragma region Player等のオブジェクト
}

void GamePlayScene::Finalize()
{

}

void GamePlayScene::Update()
{
	///JsonLoaderの更新
	for (auto object : objects) {
		object->Update();
	}

	//カメラ
	camera->Update();
	//判定マネージャー
	collisionManager->CheckAllCollisions();
}

void GamePlayScene::Draw()
{
	Object3d::PreDraw(directXCom->GetCommandList());
	//オブジェクト
	
	//JsonLoaderの描画
	for (auto object : objects) {
		object->Draw();
	}
	Object3d::PostDraw();
}

void GamePlayScene::LoadMap()
{
	//オブジェクトの読み込み
	//Model* wall = Model::LoadFromOBJ("fileName");

	for (auto& objectData : jsonLoader->objects) {
		
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (objectData.fileName == "floor")
		{
			//if (it != models.end()) { floor = it->second; }
			////モデルを指定して3Dオブジェクトを生成
			//
			////サイズ
			//DirectX::XMFLOAT3 scale;
			//DirectX::XMStoreFloat3(&scale, objectData.scaling);

			////回転角
			//DirectX::XMFLOAT3 rot;
			//DirectX::XMStoreFloat3(&rot, objectData.rotation);

			////座標
			//DirectX::XMFLOAT3 pos;
			//DirectX::XMStoreFloat3(&pos, objectData.position);

			////コライダー
			///*DirectX::XMFLOAT3 center;
			//DirectX::XMFLOAT2 radius;
			//DirectX::XMStoreFloat3(&center, objectData.center);
			//DirectX::XMStoreFloat2(&radius, objectData.size);*/

			////配列に登録
			//objects.push_back(objWall);
		}

	}
}
