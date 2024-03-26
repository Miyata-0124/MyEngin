#include "header/Game/GamePlayScene.h"
#include "header/Game/GameTitleScene.h"
#include "header/Game/GameSceneManager.h"

#include "header/3D/FbxObject3D.h"

#include "header/Game/Player.h"
#include "header/Game/enemy.h"
#include "header/Game/APBox.h"
#include "header/Game/Pipe.h"
#include "header/Game/Wall.h"
#include "header/Game/KeepsWall.h"
#include "header/Game/MoveGate.h"
#include "header/Game/Gate.h"
#include "header/Game/ClearBox.h"
#include "header/Game/Rain.h"
#include "easing/Easing.h"

void GamePlayScene::Initialize(ViewProjection* camera_, Input* input_)
{
	camera = camera_;
	input = input_;

	//スプライト共通部分の初期化
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "white1x1.png");
	spriteCommon->Loadtexture(2, "Rule.png");
	spriteCommon->Loadtexture(3, "sample.png");
	spriteCommon->Loadtexture(4, "ap.png");
	spriteCommon->Loadtexture(5, "noAP.png");
	//一度しか宣言しない
	Object3d::StaticInitialize(directXCom->GetDevice(), camera);
	FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	Particle::StaticInitialize(directXCom->GetDevice(), camera);
	//目覚め
	wakeUp = std::make_unique<WakeUp>();
	wakeUp->Initialize(spriteCommon);
	//暗転
	blackOut = std::make_unique<BlackOut>();
	blackOut->Initialize(spriteCommon);
	//AP
	ap = std::make_unique<AP>();
	ap->Initialize(spriteCommon);
	//背景
	back = std::make_unique<Sprite>();
	back->Initialize(spriteCommon, 3);
	back->SetSize({ 1280,720 });
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
	//	//モデル
	//プレイヤーモデル
	Model* playerModel = Model::LoadFromOBJ("sphere");
	//Model* ground = Model::LoadFromOBJ("blue");
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

	//背景
	//objBackGround = BackGround::Create(backGround);
#pragma endregion


#pragma region パーティクル関係
	//rain = Rain::Create();
#pragma	endregion
}

void GamePlayScene::Finalize()
{
	//オブジェクト
	wakeUp.reset();
	blackOut.reset();
	ap.reset();
	back.reset();
	delete objPlayer;
	delete objBackGround;
	for (auto object : objects) {
		delete object;
	}
}

void GamePlayScene::Update()
{
	//タイトルに戻す
	/*GameBaseScene* scene = new GameTitleScene();
	sceneManager->SetNextScene(scene);*/
	
	//フェードアウト
	wakeUp->Update();
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

	//マップ移動
	if (objClearBox->GetIsGoal() == true)
	{
		if (input->TriggerKey(DIK_V))
		{
			GameBaseScene* scene = new GameTitleScene();
			sceneManager->SetNextScene(scene);
		}
	}

	//カメラ
	camera->Update();
	back->Update();

#pragma region 各クラス間の情報受け渡し
	ap->SetAP(objPlayer->GetAP());
#pragma endregion
	//判定マネージャー
	collisionManager->CheckAllCollisions();

	/*if (objGate->GetMapMove())
	{
		blackOut->Update();
		if (blackOut->GetMinAlpha() > blackOut->GetMaxAlpha())
		{
			objGate->SetMapMove(false);
			objPlayer->SetPosition({ -20,-13,0 });

			GameBaseScene* scene = new GameClearScene();
			sceneManager->SetNextScene(scene);
		}
	}*/
}

void GamePlayScene::Draw()
{
	back->Draw();
	Object3d::PreDraw(directXCom->GetCommandList());
	//オブジェクト
	//object1->Draw(directXCom->GetCommandList());

	//プレイヤー
	objPlayer->Draw();
	//JsonLoaderの描画
	for (auto object : objects) {
		object->Draw();
	}
	Object3d::PostDraw();
	// UI,演出関連
	wakeUp->Draw();
	blackOut->Draw();
	ap->Draw();
	
}

void GamePlayScene::LoadMap()
{
	//地面に接している壁オブジェクト
	Model* wall = Model::LoadFromOBJ("wall");
	Model* floor = Model::LoadFromOBJ("floor");
	Model* box = Model::LoadFromOBJ("box");
	Model* pipe = Model::LoadFromOBJ("pipe");
	Model* apBox = Model::LoadFromOBJ("apBox");
	//クリア範囲
	Model* clear = Model::LoadFromOBJ("clear");

	for (auto& objectData : jsonLoader->objects) {
		
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (objectData.fileName == "floor")
		{
			if (it != models.end()) { floor = it->second; }
			//モデルを指定して3Dオブジェクトを生成
			objWall = Floor::Create(floor);
			//サイズ
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objWall->SetScale(scale);
			objWall->SetRadius({ scale.x,scale.y });

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
			if (it != models.end()) { wall = it->second; }
			//移動用ゲート
			objKeepsWall = Wall::Create(wall);
			//サイズ
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objKeepsWall->SetScale(scale);
			objKeepsWall->SetRadius({ scale.x,scale.y });

			//回転角
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			objKeepsWall->SetRotation(rot);

			//座標
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.position);
			objKeepsWall->SetPosition(pos);

			//半径をオブジェクトのサイズに合わせる
			objKeepsWall->SetRadius({ scale.x,scale.y });

			//配列に登録
			objects.push_back(objKeepsWall);
		}

		if (objectData.fileName == "item")
		{
			if (it != models.end()) { apBox = it->second; }
			//モデルを指定して3Dオブジェクトを生成
			objAP = APBox::Create(apBox);
			//サイズ
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objAP->SetScale(scale);
			objAP->SetRadius({ scale.x,scale.y });

			//回転角
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			objAP->SetRotation(rot);

			//座標
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.position);
			objAP->SetPosition(pos);

			//配列に登録
			objects.push_back(objAP);
		}

		if (objectData.fileName == "box")
		{
			if (it != models.end()) { box = it->second; }
			//モデルを指定して3Dオブジェクトを生成
			objWall = Floor::Create(box);
			//サイズ
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objWall->SetScale(scale);
			objWall->SetRadius({ scale.x,scale.y });

			//回転角
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			objWall->SetRotation(rot);

			//座標
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.position);
			objWall->SetPosition(pos);

			//配列に登録
			objects.push_back(objWall);
		}

		if (objectData.fileName == "pipe")
		{
			if (it != models.end()) { pipe = it->second; }
			//移動用ゲート
			objPipe = Pipe::Create(pipe);
			//サイズ
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objPipe->SetScale(scale);
			objPipe->SetRadius({ scale.x,scale.y });

			//回転角
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			objPipe->SetRotation(rot);

			//座標
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.position);
			objPipe->SetPosition(pos);

			//配列に登録
			objects.push_back(objPipe);
		}

		if (objectData.fileName == "goal")
		{
			if (it != models.end()) { clear = it->second; }
			//移動用ゲート
			objClearBox = ClearBox::Create(clear);
			//座標
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objClearBox->SetScale(scale);

			//回転角
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			objClearBox->SetRotation(rot);

			//座標
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.position);
			objClearBox->SetPosition(pos);

			//配列に登録
			objects.push_back(objClearBox);
		}
	}
}
