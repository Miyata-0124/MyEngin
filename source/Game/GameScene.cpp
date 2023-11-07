#include "header/Game/GameScene.h"
#include "header/Collider/SphereCollider.h"
#include "header/Collider/PlaneCollider.h"
#include "header/Collider/BoxCollider.h"
#include "header/Collider/CollisionManager.h"
#include "header/Game/Player.h"
#include "header/Game/enemy.h"
#include "header/Game/Floor.h"
#include "header/Game/Item.h"
#include "header/Game/Wall.h"
#include "header/Game/Gate.h"
#include "header/Game/Rain.h"
#include "header/Game/ClearBox.h"
#include "easing/Easing.h"
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
	directXCom = new DirectXCommon;
	directXCom->Initialize(winApp);

	//FBX関連
	FbxLoader::GetInstance()->Initialize(directXCom->GetDevice());

	//キー情報
	input = new	Input;
	input->Initialize(winApp);

	//DirectX初期化処理　　ここまで
#pragma	endregion
	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "taitle.png");
	spriteCommon->Loadtexture(2, "white1x1.png");
	spriteCommon->Loadtexture(3, "GameOver.png");
	spriteCommon->Loadtexture(4, "GameClear.png");
	//ViewProjection
	camera = new ViewProjection();
	camera->Initialeze();
//一度しか宣言しない
	Object3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	Particle::StaticInitialize(directXCom->GetDevice(),camera);
	//スプライト
	//タイトル
	titleSprite->Initialize(spriteCommon);
	//クリア
	clearSprite->Initialize(spriteCommon);
	//ゲームオーバー
	overSprite->Initialize(spriteCommon);
	//暗転
	blackOut->Initialize(spriteCommon);

	jsonLoader = JsonLoader::LoadFlomJSONInternal("map");

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
	Model* playerModel = Model::LoadFromOBJ("player");
	//Model* ground = Model::LoadFromOBJ("blue");
	Model* item_ = Model::LoadFromOBJ("Item");
	Model* backGround = Model::LoadFromOBJ("BG");
	Model* clear = Model::LoadFromOBJ("clear");
	Model* gate = Model::LoadFromOBJ("gate");
#pragma endregion
#pragma region Player等のオブジェクト

	collisionManager = CollisionManager::GetInstance();
	//プレイヤー
	objPlayer = Player::Create(playerModel);
	objPlayer->SetInput(input);
	//敵
	//objEnem = Enemy::Create(ground);
	//地面
	for (int i = 0; i < 3; i++)
	{
		objFloor[i] = Floor::Create(item_);
	}
	objFloor[1]->SetPosition({ 0, 15, 0 });
	objFloor[2]->SetSize({ 1,80,20 });
	objFloor[2]->SetPosition({ 30,0,0 });

	for (int i = 0; i < 2; i++)
	{
		objGate[i] = Gate::Create(gate);
	}
	objGate[0]->SetPosition({ -25,-40,0 });
	objGate[1]->SetPosition({ -23, 40,0 });
	objGate[0]->SetGateNum(0);
	objGate[1]->SetGateNum(1);

	objClearBox = ClearBox::Create(clear);
	//アイテム
	//objItem = Item::Create(ground);
	//objItem->SetInput(input);
	//壁	
	//objWall = Wall::Create(ground);
	
	//背景
	objBackGround = BackGround::Create(backGround);
#pragma endregion
	//LoadMap();
	
	#pragma region パーティクル関係
	rain = Rain::Create(1);
	#pragma	endregion
}

void GameScene::Update()
{
	//キー情報
	input->Update();
	

	switch (scene)
	{
	case 0: //タイトル画面 雨が降っているように見えるタイトル
#pragma region パーティクル
		rain->Update();
#pragma endregion
#pragma region シーン切り替え時の処理
		

		titleSprite->Update(input,scene,isBlackOut);
		isBlackOut = titleSprite->GetBlackOut();

		//暗転させるのか判断
		blackOut->Update(scene,isBlackOut);//暗転後シーン切り替えをする
		scene = blackOut->GetScene();//切り替えた情報を渡す->切り替わる

#pragma endregion
		break;
	case 1:
		if (input->TriggerKey(DIK_R))//リセット
		{
			titleSprite->Reset();
			blackOut->Reset();
			scene = 0;
		}
		if (input->TriggerKey(DIK_2))
		{
			scene = 2;
		}

		//フェードアウト
		blackOut->Update(scene, isBlackOut);
		
		//プレイヤー
		objPlayer->Update();
		//敵
		//objEnem->Update();
		//アイテム
		//objItem -> Update();
		//地面
		for (int i = 0; i < 3; i++)
		{
			objFloor[i]->Update();
		}
		for (int i = 0; i < 2; i++)
		{
			objGate[i]->Update();
		}
		objClearBox->Update();
		//壁
		//objWall->Update();
		clearSprite->Update(objGate[1]->GetIsBlackOut());
		//背景
		objBackGround->Update();
		

		/*for (auto object : objects) {
			object->Update();
		}*/

#pragma region 各クラス間の情報受け渡し
		//オブジェクト
		//objEnem->SetPPosition(objPlayer->GetPosition());
		/*objItem->SetPPosition(objPlayer->GetPosition());
		objItem->SetRetention(objPlayer->GetRetention());
		objItem->SetDirection(objPlayer->GetDirection());*/
		for (int i = 0; i < 2; i++) {
			objGate[i]->SetIsGoal(objClearBox->GetIsGoal());
		}
		blackOut->SetIsGoal(objGate[1]->GetIsBlackOut());
#pragma endregion
		//判定マネージャー
		collisionManager->CheckAllCollisions();

		break;
	case 2:
		rain->Update();
		overSprite->Update();
		break;
	}

	//カメラ
	camera->Update();
}

void GameScene::Draw()
{
	//描画処理ここから↓
	directXCom->PreDraw();

	Particle::PreDraw(directXCom->GetCommandList());

	switch (scene)
	{
	case 0:
		
		//タイトル
		titleSprite->Draw();

		rain->Draw();
		//暗転用
		blackOut->Draw();
		break;

	case 1:
		Object3d::PreDraw(directXCom->GetCommandList());
		//背景
		
		//オブジェクト
		//object1->Draw(directXCom->GetCommandList());
		
		//プレイヤー
		objPlayer->Draw();
		//敵
		//objEnem->Draw();
		//アイテム
		//objItem->Draw();
		//地面
		for (int i = 0; i < 3; i++)
		{
			objFloor[i]->Draw();
		}
		//ゴールゲート
		for (int i = 0; i < 2; i++)
		{
			objGate[i]->Draw();
		}
		objClearBox->Draw();
		//壁
		//objWall->Draw();
		//背景
		objBackGround->Draw();
		//
		/*for (auto object : objects) {
			object->Draw();
		}*/


		// UI,演出関連
		blackOut->Draw();
		clearSprite->Draw();
		Object3d::PostDraw();
		break;
	case 2:
		rain->Draw();
		overSprite->Draw();
		break;
	}

	directXCom->PostDraw();
	Particle::PostDraw();
	//ここまで↑
}

void GameScene::Finalize()
{
	winApp->Finalize();
	FbxLoader::GetInstance()->Finalize();
	delete input;
	delete winApp;
	delete directXCom;
	delete spriteCommon;
	delete titleSprite;
	delete clearSprite;
	delete overSprite;
	delete blackOut;
	delete model;
	delete objPlayer;
	for (int i = 0; i < 3; i++)
	{
		delete objFloor[i];
	}
	for (int i = 0; i < 2; i++)
	{
		delete objGate[i];
	}
	delete objClearBox;
	delete objItem;
	delete objBackGround;
	delete rain;
	
	//delete object1;
	/*delete model1;
	delete obj3d;*/
}

void GameScene::LoadMap()
{
	for (auto& objectData : jsonLoader->objects) {
		Model* model_ = Model::LoadFromOBJ("TestBox");
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end()) { model_ = it->second; }

		// モデルを指定して3Dオブジェクトを生成
		Object3d* mapObject = Object3d::Create();
		mapObject->SetModel(model_);
		// 座標
		DirectX::XMFLOAT3 scale;
		DirectX::XMStoreFloat3(&scale, objectData.scaling);
		mapObject->SetSize(scale);

		// 回転角
		DirectX::XMFLOAT3 rot;
		DirectX::XMStoreFloat3(&rot, objectData.rotation);
		mapObject->SetRotation(rot);

		// 座標
		DirectX::XMFLOAT3 pos;
		DirectX::XMStoreFloat3(&pos, objectData.position);
		mapObject->SetPosition(pos);

		//コライダー
		DirectX::XMFLOAT3 center;
		DirectX::XMFLOAT2 radius;
		DirectX::XMStoreFloat3(&center, objectData.center);
		DirectX::XMStoreFloat2(&radius, objectData.size);

		mapObject->SetCollider(new BoxCollider({ center.x,center.y+radius.y/2,center.z }, { radius.x/2,radius.y/2 }));
		// 配列に登録
		objects.push_back(mapObject);
	}
}
