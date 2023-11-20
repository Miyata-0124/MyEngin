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
	spriteCommon->Loadtexture(3, "GamePlay.png");
	spriteCommon->Loadtexture(4, "GamePlay2.png");
	spriteCommon->Loadtexture(5, "GamePlay3.png");
	//一度しか宣言しない
	Object3d::StaticInitialize(directXCom->GetDevice(), camera);
	//FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	Particle::StaticInitialize(directXCom->GetDevice(), camera);
	//目覚め
	wakeUp->Initialize(spriteCommon);

	blackOut->Initialize(spriteCommon);

	sprite[0]->Initialize(spriteCommon, 3);
	sprite[1]->Initialize(spriteCommon, 4);
	sprite[2]->Initialize(spriteCommon, 5);
	for (int i = 0; i < 3; i++)
	{
		sprite[i]->SetAnchorPoint(XMFLOAT2(0, 0));
	}
	sprite[0]->SetSize(XMFLOAT2(WinApp::window_width, 360));
	sprite[1]->SetSize(XMFLOAT2(WinApp::window_width, 360));
	sprite[2]->SetSize(XMFLOAT2(WinApp::window_width, 360));
	sprite[0]->SetPosition({ 0,0 });
	sprite[1]->SetPosition({ 100,0 });
	sprite[2]->SetPosition({ 320,200 });
	
	//jsonLoader = JsonLoader::LoadFlomJSONInternal("map");

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
	Model* ground = Model::LoadFromOBJ("blue");
	Model* item_ = Model::LoadFromOBJ("Item");
	Model* wall = Model::LoadFromOBJ("wall");
	//Model* pipe = Model::LoadFromOBJ("pipe");
	//Model* backGround = Model::LoadFromOBJ("BG");
	//Model* clear = Model::LoadFromOBJ("clear");
	Model* gate = Model::LoadFromOBJ("gate");
#pragma endregion
#pragma region Player等のオブジェクト

	//プレイヤー
	objPlayer = Player::Create(playerModel);
	objPlayer -> SetInput(input);
	//敵
	//objEnem = Enemy::Create(ground);
	//地面
	objFloor = Floor::Create(item_);
	//壁	
	objWall = Wall::Create(gate);
	//アイテム
	objItem = Item::Create(ground);
	objItem->SetInput(input);

	//移動用ゲート
	objGate = MoveGate::Create(wall);
	objGate->SetInput(input);
	//背景
	//objBackGround = BackGround::Create(backGround);
#pragma endregion
	//LoadMap();

#pragma region パーティクル関係
	rain = Rain::Create();
#pragma	endregion
}

void GamePlayScene::Finalize()
{
	//オブジェクト
	delete objPlayer;
	delete objFloor;
	/*for (int i = 0; i < 2; i++)
	{
		delete objGate[i];
	}*/
	delete objWall;
	delete objItem;
	delete objBackGround;
	delete objGate;
	delete rain;
	delete wakeUp;
	delete blackOut;
	for (int i = 0; i < 3; i++)
	{
		delete sprite[i];
	}
}

void GamePlayScene::Update()
{
	if (map == MAP::MAP1)
	{
		//フェードアウト
		wakeUp->Update();
		if (objGate->GetMapMove())
		{
			blackOut->Update();
			if (blackOut->GetMinAlpha() > blackOut->GetMaxAlpha())
			{
				objPlayer->SetPosition({ -20,-13,0 });
				objGate->SetMapMove(false);
				blackOut->Reset();
				map = MAP::MAP2;
			}
		}

		sprite[0]->Update();
		sprite[2]->Update();
	}
	else if (map == MAP::MAP2)
	{
		//壁
		objWall->Update();
		//アイテム
		objItem->Update();

		if (objGate->GetMapMove())
		{
			blackOut->Update();
			if (blackOut->GetMinAlpha() > blackOut->GetMaxAlpha())
			{
				objGate->SetMapMove(false);
				objPlayer->SetPosition({ -20,-13,0 });
				blackOut->Reset();

				GameBaseScene* scene = new GameClearScene();
				sceneManager->SetNextScene(scene);
			}
		}
		sprite[1]->Update();
	}
	//プレイヤー
	objPlayer->Update();
	//地面
	objFloor->Update();

	objGate->Update();
	//背景
	//objBackGround->Update();

	///JsonLoaderの更新
	/*for (auto object : objects) {
		object->Update();
	}*/

#pragma region 各クラス間の情報受け渡し
	//オブジェクト
	//objEnem->SetPPosition(objPlayer->GetPosition());
	objItem->SetPPosition(objPlayer->GetPosition());
	objItem->SetRetention(objPlayer->GetRetention());
	objItem->SetDirection(objPlayer->GetDirection());
	/*for (int i = 0; i < 2; i++) {
		objGate[i]->SetIsGoal(objClearBox->GetIsGoal());
	}
	blackOut->SetIsGoal(objGate[1]->GetIsBlackOut());*/
#pragma endregion
	//判定マネージャー
	collisionManager->CheckAllCollisions();

	camera->Update();
}

void GamePlayScene::Draw()
{
	Object3d::PreDraw(directXCom->GetCommandList());
	if (map == MAP::MAP1)
	{
		
	}
	else if (map == MAP::MAP2)
	{
		//壁
		objWall->Draw();
		//アイテム
		objItem->Draw();
	}

	//背景

	//オブジェクト
	//object1->Draw(directXCom->GetCommandList());

	//プレイヤー
	objPlayer->Draw();
	//地面
	objFloor->Draw();

	objGate->Draw();
	//背景
	//objBackGround->Draw();
	//JsonLoaderの描画
	/*for (auto object : objects) {
		object->Draw();
	}*/
	Object3d::PostDraw();
	// UI,演出関連
	if (map == MAP::MAP1)
	{
		wakeUp->Draw();

		sprite[0]->Draw();
		sprite[2]->Draw();

		blackOut->Draw();
		
	}
	else if (map == MAP::MAP2)
	{
		sprite[1]->Draw();
		blackOut->Draw();
	}
}

