#include "GameScene.h"

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

	//DirectX初期化処理　　ここまで
#pragma endregion
#pragma	endregion
//スプライト
	//スプライト共通部分の初期化
	SpriteCommon::GetInstance()->Initialize(directXCom);
	
}

void GameScene::Update()
{
	///それぞれのクラスのUpdateのみ記述
	//キー情報
	input->Update();
	//カメラ
	camera->Update();
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
	//プレイヤー
	objPlayer->Update();
	//アイテム
	objItem->Update();
	//地面
	objFloor->Update();
	//背景
	objBackGround->Update();
	//obj3d->Update();
	//particle->Update();

	for (auto object : objects) {
		object->Update();
	}

#pragma region 各クラス間の情報受け渡し
	//オブジェクト
	objItem->SetPPosition(objPlayer->GetPosition());
	objItem->SetRetention(objPlayer->GetRetention());
	objItem->SetDirection(objPlayer->GetDirection());
	//スプライト


#pragma endregion
	
	//判定マネージャー
	collisionManager->CheckAllCollisions();
}

void GameScene::Draw()
{
	//描画処理ここから↓
	directXCom->PreDraw();
	//背景


	//オブジェクト
	//object1->Draw(directXCom->GetCommandList());
	Object3d::PreDraw(directXCom->GetCommandList());
	//プレイヤー
	objPlayer->Draw();
	//アイテム
	objItem->Draw();
	//地面
	//objFloor->Draw();
	//背景
	objBackGround->Draw();
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
		Model* model = Model::LoadFromOBJ("Box");
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end()) { model = it->second; }

		// モデルを指定して3Dオブジェクトを生成
		Object3d* newObject = Object3d::Create();
		newObject->SetModel(model);
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

		////コライダー
		//DirectX::XMFLOAT3 center;
		// 配列に登録
		objects.push_back(newObject);
	}
}
