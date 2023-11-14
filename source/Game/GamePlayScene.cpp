#include "header/Game/GamePlayScene.h"
#include "header/Game/GameSceneManager.h"

#include "header/Collider/SphereCollider.h"
#include "header/Collider/PlaneCollider.h"
#include "header/Collider/BoxCollider.h"


#include "header/Game/Player.h"
#include "header/Game/enemy.h"
#include "header/Game/Floor.h"
#include "header/Game/Item.h"
#include "header/Game/Wall.h"
#include "header/Game/Gate.h"
#include "header/Game/StageGate.h"
#include "header/Game/Rain.h"
#include "header/Game/ClearBox.h"
#include "easing/Easing.h"

void GamePlayScene::Initialize(ViewProjection* camera_, Input* input_)
{
	//スプライト共通部分の初期化
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "taitle.png");
	spriteCommon->Loadtexture(2, "white1x1.png");
	spriteCommon->Loadtexture(3, "GameOver.png");
	spriteCommon->Loadtexture(4, "GameClear.png");

	//一度しか宣言しない
	Object3d::StaticInitialize(directXCom->GetDevice(), camera_);
	//FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	Particle::StaticInitialize(directXCom->GetDevice(), camera_);
	//スプライト
	
	//クリア
	clearSprite->Initialize(spriteCommon);
	//ゲームオーバー
	overSprite->Initialize(spriteCommon);
	//暗転
	blackOut->Initialize(spriteCommon);

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
	//Model* pipe = Model::LoadFromOBJ("pipe");
	//Model* backGround = Model::LoadFromOBJ("BG");
	//Model* clear = Model::LoadFromOBJ("clear");
	//Model* gate = Model::LoadFromOBJ("gate");
#pragma endregion
#pragma region Player等のオブジェクト

	//プレイヤー
	objPlayer = Player::Create(playerModel);
	objPlayer -> SetInput(input_);
	//敵
	//objEnem = Enemy::Create(ground);
	objGate = StageGate::Create(ground);
	//地面
	objFloor = Floor::Create(item_);

	/*for (int i = 0; i < 2; i++)
	{
		objGate[i] = Gate::Create(gate);
		objGate[i]->SetGateNum(i);
	}
	objGate[0]->SetPosition({ -25,-40,0 });
	objGate[1]->SetPosition({ -23, 40,0 });

	objClearBox = ClearBox::Create(clear);*/
	//アイテム
	//objItem = Item::Create(ground);
	//objItem->SetInput(input);
	//壁	
	//objWall = Wall::Create(ground);

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
	//ゲーム内スプライト
	delete clearSprite;
	delete overSprite;
	//演出
	delete blackOut;
	//オブジェクト
	delete objPlayer;
	delete objFloor;
	delete objGate;
	/*for (int i = 0; i < 2; i++)
	{
		delete objGate[i];
	}*/
	delete objClearBox;
	delete objItem;
	delete objBackGround;
	delete rain;


}

void GamePlayScene::Update()
{
	//if (input->TriggerKey(DIK_R))//リセット
	//{
	//	titleSprite->Reset();
	//	blackOut->Reset();
	//	scene = 0;
	//}

	////フェードアウト
	//blackOut->Update(scene, isBlackOut);
	//プレイヤー
	objPlayer->Update();
	//敵
	//objEnem->Update();
	//アイテム
	//objItem -> Update();
	//ステージ移動用
	objGate->Update();
	//地面
	objFloor->Update();

	/*for (int i = 0; i < 2; i++)
	{
		objGate[i]->Update();
	}
	objClearBox->Update();*/
	//壁
	//objWall->Update();
	//clearSprite->Update(objGate[1]->GetIsBlackOut());
	//背景
	//objBackGround->Update();

	///JsonLoaderの更新
	/*for (auto object : objects) {
		object->Update();
	}*/

#pragma region 各クラス間の情報受け渡し
	//オブジェクト
	//objEnem->SetPPosition(objPlayer->GetPosition());
	/*objItem->SetPPosition(objPlayer->GetPosition());
	objItem->SetRetention(objPlayer->GetRetention());
	objItem->SetDirection(objPlayer->GetDirection());*/
	/*for (int i = 0; i < 2; i++) {
		objGate[i]->SetIsGoal(objClearBox->GetIsGoal());
	}
	blackOut->SetIsGoal(objGate[1]->GetIsBlackOut());*/
#pragma endregion
	//判定マネージャー
	collisionManager->CheckAllCollisions();
}

void GamePlayScene::Draw()
{
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
	objGate->Draw();
	//地面
	objFloor->Draw();

	//ゴールゲート
	/*for (int i = 0; i < 2; i++)
	{
		objGate[i]->Draw();
	}
	objClearBox->Draw();*/
	//壁
	//objWall->Draw();
	//背景
	//objBackGround->Draw();
	//
	/*for (auto object : objects) {
		object->Draw();
	}*/


	// UI,演出関連
	blackOut->Draw();
	clearSprite->Draw();
	Object3d::PostDraw();
}

