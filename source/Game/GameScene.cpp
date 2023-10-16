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
	//ViewProjection
	camera = new ViewProjection();
	camera->Initialeze();
//一度しか宣言しない
	Object3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	Particle::StaticInitialize(directXCom->GetDevice(),camera);
	//スプライト
	sprite->Initialize(spriteCommon, 1);
	sprite->SetAnchorPoint(XMFLOAT2(0, 0));
	sprite->SetSize(XMFLOAT2(WinApp::window_width, WinApp::window_height));
	sprite->SetPosition({0,0});

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
	Model* backGround = Model::LoadFromOBJ("BG");
#pragma endregion
#pragma region Player等のオブジェクト

	collisionManager = CollisionManager::GetInstance();
	//プレイヤー
	objPlayer = Player::Create(ground);
	objPlayer->SetInput(input);
	//敵
	//objEnem = Enemy::Create(item_);
	//地面
	objFloor = Floor::Create(playerModel);
	//アイテム
	objItem = Item::Create(playerModel);
	objItem->SetInput(input);
	//壁
	objWall = Wall::Create(item_);
	//背景
	objBackGround = BackGround::Create(backGround);
#pragma endregion
	LoadMap();
	
	#pragma region パーティクル関係
	//	パーティクル
	Particle::LoadTexture(1, "blue1x1.png");
	//引数の数字はテクスチャ読み込みのインデックスナンバー
	particle = Particle::Create(1);
	#pragma	endregion
}

void GameScene::Update()
{
	//キー情報
	input->Update();
	//カメラ
	camera->Update();

	switch (scene)
	{
	case 0: //タイトル画面 雨が降っているように見えるタイトル
#pragma region パーティクル
		if (rainTimer < 10)
		{
			rainTimer++;
		}
		else
		{
			rainTimer = 0;
		}
		//雨の基盤
		if (rainTimer < 10)
		{
			//パーティクル
			for (int i = 0; i < 15; i++)
			{
				//XYZ全て[-0.05f,+0.05f]でランダムに分布
				//const	float	rnd_vel = 1.5f;
				XMFLOAT3	vel{};
				//vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

				//重力に見立ててYのみ[-0.001f,0]でランダムに分布
				const	float	rnd_acc = -0.1f;
				XMFLOAT3	acc{};
				acc.y = (float)rand() / RAND_MAX * rnd_acc;

				particle->Control(75, { (float)rand() / RAND_MAX * 100.0f - 100.0f / 2.0f,40,0}, vel, acc, 1.0f, 0.0f);
			}
		}
		particle->Update();
#pragma endregion
#pragma region シーン切り替え時の処理
		//動かすために座標を取得
		XMFLOAT2 position = sprite->GetPosition();
		if (!UIFlag) {
			if (position.x < 15)
			{
				UIspeed.x = 0.4f;
			}
			else
			{
				UIFlag = true;
			}
		}
		else
		{
			if (position.x > -15)
			{
				UIspeed.x = -0.4f;
			}
			else
			{
				UIFlag=false;
			}
		}
		position.x += UIspeed.x;
		position.y += UIspeed.y;

		//切り替え
		if (input->TriggerKey(DIK_SPACE) && !ChengeScene)
		{
			ChengeScene = true;
		}
		if (ChengeScene)
		{
			min += 0.1f;;
			y = min / max;
			position.y = startY + (endY - startY) * Easing::easeInSine(y);

			if (min>max)
			{
				min = 0.0f;
				ChengeScene = false;
				scene = 1;
			}
		}
		//移動後の座標を入れる
		sprite->SetPosition(position);

#pragma endregion
		break;
	case 1:
		//プレイヤー
		objPlayer->Update();
		//敵
		//objEnem->Update();
		//アイテム
		objItem -> Update();
		//地面
		objFloor -> Update();
		//壁
		objWall -> Update();
		
		//背景
		objBackGround->Update();
		//obj3d->Update();
		

		for (auto object : objects) {
			object->Update();
		}

#pragma region 各クラス間の情報受け渡し
		//オブジェクト
		//objEnem->SetPPosition(objPlayer->GetPosition());
		objItem->SetPPosition(objPlayer->GetPosition());
		objItem->SetRetention(objPlayer->GetRetention());
		objItem->SetDirection(objPlayer->GetDirection());
#pragma endregion
		//判定マネージャー
		collisionManager->CheckAllCollisions();

		//説明スプライト移動
#pragma region  スプライトの移動演出
		////動かすために座標を取得
		//XMFLOAT2 position = sprite->GetPosition();
		////移動後の座標を入れる
		//sprite->SetPosition(position);
#pragma endregion
		
		break;
	case 2:
		break;
	}
	
}

void GameScene::Draw()
{
	//描画処理ここから↓
	directXCom->PreDraw();
	Object3d::PreDraw(directXCom->GetCommandList());
	
	switch (scene)
	{
	case 0:
		sprite->SetIsInvisible(false);
		sprite->SetTexIndex(1);
		sprite->Draw();

		Particle::PreDraw(directXCom->GetCommandList());
		particle->Draw();
		Particle::PostDraw();

		break;
	case 1:
		
		//背景

		//オブジェクト
		//object1->Draw(directXCom->GetCommandList());
		
		//プレイヤー
		objPlayer->Draw();
		//敵
		//objEnem->Draw();
		//アイテム
		objItem->Draw();
		//地面
		//objFloor->Draw();
		//壁
		objWall->Draw();
		//背景
		objBackGround->Draw();
		for (auto object : objects) {
			object->Draw();
		}

	
	// UI関連
		sprite->SetIsInvisible(false);
		sprite->SetTexIndex(2);
		sprite->SetSize({320, 180});
		sprite->SetPosition({ -320,0 });
		sprite->Draw();

		break;
	case 2:
		break;
	}
	
	Object3d::PostDraw();
	
	directXCom->PostDraw();
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
	delete sprite;
	delete model;
	delete objPlayer;
	delete objFloor;
	delete objItem;
	delete objBackGround;
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
		//DirectX::XMFLOAT3 center;
		// 配列に登録
		objects.push_back(mapObject);
	}
}
