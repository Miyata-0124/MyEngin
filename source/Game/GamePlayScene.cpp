#include "header/Game/GamePlayScene.h"
#include "header/Game/GameSceneManager.h"

#include "header/Game/Player.h"
#include "header/Game/enemy.h"
#include "header/Game/Floor.h"
#include "header/Game/Item.h"
#include "header/Game/Wall.h"
#include "header/Game/MoveGate.h"
#include "header/Game/Rain.h"
#include "easing/Easing.h"

#include "header/Game/GameClearScene.h"

void GamePlayScene::Initialize(ViewProjection* camera_, Input* input_)
{
	camera = camera_;
	input = input_;

	//スプライト共通部分の初期化
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "white1x1.png");
	spriteCommon->Loadtexture(2, "white1x1.png");
	spriteCommon->Loadtexture(3, "Rule.png");
	//一度しか宣言しない
	Object3d::StaticInitialize(directXCom->GetDevice(), camera);
	//FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	Particle::StaticInitialize(directXCom->GetDevice(), camera);
	//目覚め
	wakeUp->Initialize(spriteCommon);

	blackOut->Initialize(spriteCommon);

	sprite->Initialize(spriteCommon, 3);
	//json読み込み
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
	//プレイヤーモデル
	Model* playerModel = Model::LoadFromOBJ("player");
	Model* ground = Model::LoadFromOBJ("blue");
	//Model* item_ = Model::LoadFromOBJ("Item");
#pragma endregion
#pragma region Player等のオブジェクト

	//プレイヤー
	objPlayer = Player::Create(playerModel);
	objPlayer -> SetInput(input);
	//敵
	//objEnem = Enemy::Create(ground);
	//地面
	//objFloor = Floor::Create(item_);
	//アイテム
	objItem = Item::Create(ground);
	objItem->SetInput(input);

	
	//背景
	//objBackGround = BackGround::Create(backGround);
#pragma endregion
	//マップ読み込み
	LoadMap();

#pragma region パーティクル関係
	//rain = Rain::Create();
#pragma	endregion
}

void GamePlayScene::Finalize()
{
	//オブジェクト
	delete objPlayer;
	//delete objFloor;
	delete objItem;
	delete objBackGround;
	//delete rain;
	delete wakeUp;
	delete blackOut;
	delete sprite;
	for (auto object : objects) {
		delete object;
	}
	blackOut->Reset();
}

void GamePlayScene::Update()
{
	//フェードアウト
	wakeUp->Update();
	//アイテム
	objItem->Update();
	//プレイヤー
	objPlayer->Update();
	//地面
	//objFloor->Update();
	//背景
	//objBackGround->Update();

	///JsonLoaderの更新
	for (auto object : objects) {
		object->Update();
	}

	//カメラ
	camera->Update();


	sprite->Update();

#pragma region 各クラス間の情報受け渡し
	//オブジェクト
	//objEnem->SetPPosition(objPlayer->GetPosition());
	objPlayer->SetIsStop(objItem->GetIsStop());
	objItem->SetPPosition(objPlayer->GetPosition());
	objItem->SetRetention(objPlayer->GetRetention());
	objItem->SetDirection(objPlayer->GetDirection());
#pragma endregion
	//判定マネージャー
	collisionManager->CheckAllCollisions();

	if (objGate->GetMapMove())
	{
		blackOut->Update();
		if (blackOut->GetMinAlpha() > blackOut->GetMaxAlpha())
		{
			objGate->SetMapMove(false);
			objPlayer->SetPosition({ -20,-13,0 });

			GameBaseScene* scene = new GameClearScene();
			sceneManager->SetNextScene(scene);
		}
	}
}

void GamePlayScene::Draw()
{
	Object3d::PreDraw(directXCom->GetCommandList());
	//オブジェクト
	//object1->Draw(directXCom->GetCommandList());

	//プレイヤー
	objPlayer->Draw();
	//地面
	//objFloor->Draw();
	//アイテム
	objItem->Draw();
	//背景
	//objBackGround->Draw();
	//JsonLoaderの描画
	for (auto object : objects) {
		object->Draw();
	}
	Object3d::PostDraw();
	// UI,演出関連
	sprite->Draw();
	wakeUp->Draw();
	blackOut->Draw();
	
}

void GamePlayScene::LoadMap()
{
	for (auto& objectData : jsonLoader->objects) {
		//地面に接している壁オブジェクト
		Model* model = Model::LoadFromOBJ("wall");
		//次のステージへ移動するためのオブジェクト
		Model* backGround = Model::LoadFromOBJ("BG");
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (objectData.fileName == "floor")
		{
			if (it != models.end()) { model = it->second; }
			//モデルを指定して3Dオブジェクトを生成
			objWall = Wall::Create(model);
			//座標
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objWall->SetScale(scale);

			//回転角
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			objWall->SetRotation(rot);

			//座標
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.position);
			objWall->SetPosition(pos);

			//コライダー
			/*DirectX::XMFLOAT3 center;
			DirectX::XMFLOAT2 radius;
			DirectX::XMStoreFloat3(&center, objectData.center);
			DirectX::XMStoreFloat2(&radius, objectData.size);*/

			//配列に登録
			objects.push_back(objWall);
		}

		if (objectData.fileName == "wall")
		{

		}

		if (objectData.fileName == "moveGate")
		{
			if (it != models.end()) { backGround = it->second; }
			//移動用ゲート
			objGate = MoveGate::Create(backGround);
			objGate->SetInput(input);
			//座標
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objGate->SetScale(scale);

			//回転角
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			objGate->SetRotation(rot);

			//座標
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.position);
			objGate->SetPosition(pos);

			//配列に登録
			objects.push_back(objGate);
		}
	}
}
