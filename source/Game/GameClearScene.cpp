#include "header/Game/GameClearScene.h"
#include "header/Game/GameSceneManager.h"

#include "header/Game/Player.h"
#include "header/Game/Gate.h"
#include "header/Game/ClearBox.h"
#include "header/Game/Wall.h"
#include "header/Game/MoveGate.h"

#include "header/Game/Rain.h"

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

	//json読み込み
	jsonLoader = JsonLoader::LoadFlomJSONInternal("sherter");

	//プレイヤーモデル
	Model* playerModel = Model::LoadFromOBJ("player");
	//地面仮モデル
	//Model* item_ = Model::LoadFromOBJ("Item");

	//プレイヤー
	objPlayer = Player::Create(playerModel);
	objPlayer->SetInput(input);

#pragma region パーティクル関係
	rain = Rain::Create();
#pragma	endregion

	//マップ読み込み
	LoadMap();
}

void GameClearScene::Finalize()
{
	delete rain;
	delete blackOut;
	delete clearSprite;
	delete objPlayer;
	for (auto object : objects) {
		delete object;
	}
}

void GameClearScene::Update()
{
#pragma region パーティクル
	rain->Update();
#pragma endregion
	//プレイヤー
	if (!objClearBox->GetIsGoal())
	{
		objPlayer->Update();
	}
	
	for (auto object : objects) {
		object->Update();
	}
	if (objGate->GetRotation().x >= 90.0f)
	{
		blackOut->Update();
	}

	if (blackOut->GetMinAlpha() > blackOut->GetMaxAlpha())
	{
		clearSprite->Update();
	}
	//判定マネージャー
	collisionManager->CheckAllCollisions();

	//各クラスに情報を渡す
	objGate->SetIsGoal(objClearBox->GetIsGoal());

	if (input->TriggerKey(DIK_R))
	{
		GameBaseScene* scene = new GameTitleScene();
		sceneManager->SetNextScene(scene);
	}

}

void GameClearScene::Draw()
{
	Particle::PreDraw(directXCom->GetCommandList());
	rain->Draw();
	Particle::PostDraw();

	Object3d::PreDraw(directXCom->GetCommandList());
	//プレイヤー
	objPlayer->Draw();
	for (auto object : objects) {
		object->Draw();
	}
	objClearBox->Draw();


	Object3d::PostDraw();

	blackOut->Draw();
	clearSprite->Draw();
}

void GameClearScene::LoadMap()
{
	for (auto& objectData : jsonLoader->objects) {
		//地面に接している壁オブジェクト
		Model* model = Model::LoadFromOBJ("wall");
		//次のステージへ移動するためのオブジェクト
		//Model* backGround = Model::LoadFromOBJ("BG");
		//扉
		Model* gate = Model::LoadFromOBJ("gate");

		Model* clear = Model::LoadFromOBJ("clear");

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

		if (objectData.fileName == "Gate")
		{
			if (it != models.end()) { gate = it->second; }
			//モデルを指定して3Dオブジェクトを生成
			objGate = Gate::Create(gate);
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

			//コライダー
			/*DirectX::XMFLOAT3 center;
			DirectX::XMFLOAT2 radius;
			DirectX::XMStoreFloat3(&center, objectData.center);
			DirectX::XMStoreFloat2(&radius, objectData.size);*/

			//配列に登録
			objects.push_back(objGate);
		}

		if (objectData.fileName == "MoveGate")
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
