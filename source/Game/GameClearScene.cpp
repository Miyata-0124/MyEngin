#include "header/Game/GameClearScene.h"
#include "header/Game/GameSceneManager.h"

#include "header/Game/Player.h"
#include "header/Game/Floor.h"
#include "header/Game/Gate.h"
#include "header/Game/ClearBox.h"

#include "easing/Easing.h"

#include "header/Game/GameTitleScene.h"

void GameClearScene::Initialize(ViewProjection* camera_, Input* input_)
{
	camera = camera_;
	input = input_;

	//スプライト共通部分の初期化
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "GameClear.png");
	spriteCommon->Loadtexture(2, "white1x1.png");

	//クリア
	clearSprite->Initialize(spriteCommon);
	//暗転
	blackOut->Initialize(spriteCommon);

	//一度しか宣言しない
	Object3d::StaticInitialize(directXCom->GetDevice(), camera);

	//プレイヤーモデル
	Model* playerModel = Model::LoadFromOBJ("player");
	//地面仮モデル
	Model* item_ = Model::LoadFromOBJ("Item");
	//扉
	Model* gate = Model::LoadFromOBJ("gate");

	Model* clear = Model::LoadFromOBJ("clear");
	//プレイヤー
	objPlayer = Player::Create(playerModel);
	objPlayer->SetInput(input);
	//地面
	for (int i = 0; i < 3; i++)
	{
		objFloor[i] = Floor::Create(item_);
	}
	objFloor[1]->SetPosition({ 0, 15, 0 });
	objFloor[2]->SetSize({ 1,80,20 });
	objFloor[2]->SetPosition({ 30,0,0 });
	//扉
	for (int i = 0; i < 2; i++)
	{
		objGate[i] = Gate::Create(gate);
		objGate[i]->SetGateNum(i);
	}
	objGate[0]->SetPosition({ -25,-40,0 });
	objGate[1]->SetPosition({ -23, 40,0 });

	objClearBox = ClearBox::Create(clear);
}

void GameClearScene::Finalize()
{
	delete blackOut;
	delete clearSprite;
	delete objPlayer;
	delete objClearBox;
	for (int i = 0; i < 3; i++)
	{
		delete objFloor[i];
	}
	for (int i = 0; i < 2; i++)
	{
		delete objGate[i];
	}
}

void GameClearScene::Update()
{
	//プレイヤー
	if (!objClearBox->GetIsGoal())
	{
		objPlayer->Update();
	}
	
	//地面
	for (int i = 0; i < 3; i++)
	{
		objFloor[i]->Update();
	}
	//扉
	for (int i = 0; i < 2; i++)
	{
		objGate[i]->Update();
		if (objGate[i]->GetRotation().x >= 90.0f)
		{
			blackOut->Update();
		}
	}
	if (blackOut->GetMinAlpha() > blackOut->GetMaxAlpha())
	{
		clearSprite->Update();
	}

	if (input->TriggerKey(DIK_R))
	{
		GameBaseScene* scene = new GameTitleScene();
		sceneManager->SetNextScene(scene);
	}

	//判定用
	objClearBox->Update();

	//各クラスに情報を渡す
	for (int i = 0; i < 2; i++) {
		objGate[i]->SetIsGoal(objClearBox->GetIsGoal());
	}

	//判定マネージャー
	collisionManager->CheckAllCollisions();
}

void GameClearScene::Draw()
{
	Object3d::PreDraw(directXCom->GetCommandList());
	//プレイヤー
	objPlayer->Draw();
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


	Object3d::PostDraw();

	blackOut->Draw();
	clearSprite->Draw();
}
