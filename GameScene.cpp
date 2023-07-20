#include "GameScene.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Floor.h"
#include "Item.h"
#include <sstream>
#include <iomanip>
#include <imgui.h>

void GameScene::Initialize()
{
#pragma region WindowsAPIの初期化
	winApp = new	WinApp;
	winApp->Initialize();
#pragma endregion

#pragma region DirectX初期化処理
	//DirectX初期化処理　　ここから
	directXCom = new DirectXCommon;
	directXCom->Initialize(winApp);

	//FBX関連
	FbxLoader::GetInstance()->Initialize(directXCom->GetDevice());

	//キー情報
	input = new	Input;
	input->Initialize(winApp);

	imgui = new ImguiManager;
	imgui->Initialize(winApp, directXCom);
	//DirectX初期化処理　　ここまで
#pragma endregion
#pragma	endregion
//スプライト
	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "MK.png");
	spriteCommon->Loadtexture(2, "test.png");
#pragma	region	シーンの初期化
	//ViewProjection
	
//一度しか宣言しない
	Object3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	//Particle::StaticInitialize(directXCom->GetDevice(), camera.get());
	//スプライト
	sprite->Initialize(spriteCommon, 1);
	sprite->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	sprite->SetSize(XMFLOAT2(320.0f, 180.0f));
	sprite->SetPosition({ 160,90 });

	jsonLoader = JsonLoader::LoadFlomJSONInternal("test");

#pragma region FBX
	/*model = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

	object1->initialize();
	object1->SetModel(model);
	object1->SetRotation({ 0,60,0 });
	object1->SetPosition({ 0,-3,0 });
	object1->PlayAnimation();*/
#pragma endregion
#pragma region モデル
	//	//モデル
	//Model* model1 = Model::LoadFromOBJ("wall");
	//プレイヤーモデル
	Model* playerModel = Model::LoadFromOBJ("Box");
	Model* ground = Model::LoadFromOBJ("blue");
	Model* item_ = Model::LoadFromOBJ("Item");
#pragma endregion
#pragma region Player等のオブジェクト

	collisionManager = CollisionManager::GetInstance();
	objPlayer = Player::Create(playerModel);
	objPlayer->SetInput(input);
	objPlayer->Initialize();
	objFloor = Floor::Create(ground);
	objFloor->Initialize();
	objItem = Item::Create(item_);
	objItem->Initialize();
	//コライダー追加
	objPlayer->SetCollider(new SphereCollider);
	objItem->SetCollider(new SphereCollider);
	objFloor->SetCollider(new PlaneCollider);
#pragma endregion
	//LoadMap();
	
	#pragma region パーティクル関係
		//パーティクル
		//Particle::LoadTexture(1, "MK.png");
		//Particle::LoadTexture(2, "testpar1.png");
		//Particle* particle = nullptr;
		//// 引数の数字はテクスチャ読み込みのインデックスナンバー
		//particle = Particle::Create(1);
		//particle->Update();
	#pragma	endregion
}

void GameScene::Update()
{
	///それぞれのクラスのUpdateのみ記述
	//キー情報
	input->Update();
	
#pragma region パーティクル
	//パーティクル発生
	//if (input->TriggerKey(DIK_F))
	//{
	//	//パーティクル
	//	for (int i = 0; i < 100; i++)
	//	{
	//		//XYZ全て[-0.05f,+0.05f]でランダムに分布
	//		const	float	rnd_vel = 0.1f;
	//		XMFLOAT3	vel{};
	//		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	//		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	//		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

	//		//重力に見立ててYのみ[-0.001f,0]でランダムに分布
	//		const	float	rnd_acc = 0.001f;
	//		XMFLOAT3	acc{};
	//		acc.y = (float)rand() / RAND_MAX * rnd_acc;

	//		particle->Control(100, obj3d->GetPosition(), vel, acc, 1.0f, 0.0f);
	//	}
	//}
#pragma endregion
#pragma region スプライト移動
		/*{
			XMFLOAT2 position = sprite->GetPosition();
			if (input->PushKey(DIK_UP))
			{
				position.y -= 10.0f;
			}
			else if (input->PushKey(DIK_DOWN))
			{
				position.y += 10.0f;
			}
			if (input->PushKey(DIK_LEFT))
			{
				position.x -= 10.0f;
			}
			else if (input->PushKey(DIK_RIGHT))
			{
				position.x += 10.0f;

			}
			sprite->SetPosition(position);
		}*/
#pragma endregion
	objPlayer->Update();
	objItem->Update();
	objFloor->Update();
	//obj3d->Update();
	//particle->Update();

	for (auto object : objects) {
		object->Update();
	}

	//判定マネージャー
	collisionManager->CheckAllCollisions();

	imgui->Begin();
	ImGui::ShowDemoWindow();
	imgui->End();
}

void GameScene::Draw()
{
	//描画処理ここから↓
	directXCom->PreDraw();
	//背景


	//オブジェクト
	//object1->Draw(directXCom->GetCommandList());
	Object3d::PreDraw(directXCom->GetCommandList());
	objPlayer->Draw();
	objItem->Draw();
	objFloor->Draw();

	for (auto object : objects) {
		object->Draw();
	}

	Object3d::PostDraw();
#pragma region パーティクル

	//Particle::PreDraw(directXCom->GetCommandList());
	//particle->Draw();
	//Particle::PostDraw();

#pragma endregion

	// UI関連
	sprite->SetIsInvisible(false);
	sprite->SetTexIndex(1);
	sprite->Draw();

	imgui->Draw();

	directXCom->PostDraw();
	//ここまで↑
}

void GameScene::Finalize()
{
	winApp->Finalize();
	FbxLoader::GetInstance()->Finalize();
	imgui->Finalize();
	delete input;
	delete winApp;
	delete directXCom;
	delete spriteCommon;
	delete sprite;
	delete model;
	delete object1;
	/*delete model1;
	delete obj3d;*/
}

void GameScene::LoadMap()
{
	for (auto& objectData : jsonLoader->objects) {
		Model* model = Model::LoadFromOBJ("Box");
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end()) { model = it->second; }

		// モデルを指定して3Dオブジェクトを生成
		Object3d* newObject = Object3d::Create();
		newObject->SetModel(model);

		newObject->SetCollider(new SphereCollider);

		// 座標
		DirectX::XMFLOAT3 scale;
		DirectX::XMStoreFloat3(&scale, objectData.scaling);
		newObject->SetSize(scale);

		// 回転角
		DirectX::XMFLOAT3 rot;
		DirectX::XMStoreFloat3(&rot, objectData.rotation);
		newObject->SetRotation(rot);

		// 座標
		DirectX::XMFLOAT3 pos;
		DirectX::XMStoreFloat3(&pos, objectData.position);
		newObject->SetPosition(pos);

		// 配列に登録
		objects.push_back(newObject);
	}
}
