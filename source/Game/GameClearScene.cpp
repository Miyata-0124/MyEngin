#include "header/Game/GameClearScene.h"
#include "header/Game/GameSceneManager.h"
#include "easing/Easing.h"

void GameClearScene::Initialize(ViewProjection* camera_, Input* input_)
{
	camera = camera_;
	input = input_;

	//スプライト共通部分の初期化
	spriteCommon->Initialize(directXCom);
	//spriteCommon->Loadtexture(1, "fileName");

	//一度しか宣言しない
	Object3d::StaticInitialize(directXCom->GetDevice(), camera);

	//json読み込み
	jsonLoader = JsonLoader::LoadFlomJSONInternal("sherter");

	//マップ読み込み
	LoadMap();
}

void GameClearScene::Finalize()
{
	//jsonLoaderで作成した物の削除
	for (auto object : objects) {
		delete object;
	}
}

void GameClearScene::Update()
{
	//jsonの更新
	for (auto object : objects) {
		object->Update();
	}

	//判定マネージャー
	collisionManager->CheckAllCollisions();
}

void GameClearScene::Draw()
{
	Object3d::PreDraw(directXCom->GetCommandList());
	
	for (auto object : objects) {
		object->Draw();
	}

	Object3d::PostDraw();
}

void GameClearScene::LoadMap()
{
	for (auto& objectData : jsonLoader->objects) {
		//地面に接している壁オブジェクト
		Model* model = Model::LoadFromOBJ("wall");

		decltype(models)::iterator it = models.find(objectData.fileName);
		if (objectData.fileName == "floor")
		{
			if (it != models.end()) { model = it->second; }
			////モデルを指定して3Dオブジェクトを生成
			//objWall = Floor::Create(model);
			////座標
			//DirectX::XMFLOAT3 scale;
			//DirectX::XMStoreFloat3(&scale, objectData.scaling);
			//objWall->SetScale(scale);

			////回転角
			//DirectX::XMFLOAT3 rot;
			//DirectX::XMStoreFloat3(&rot, objectData.rotation);
			//objWall->SetRotation(rot);

			////座標
			//DirectX::XMFLOAT3 pos;
			//DirectX::XMStoreFloat3(&pos, objectData.position);
			//objWall->SetPosition(pos);

			////コライダー
			///*DirectX::XMFLOAT3 center;
			//DirectX::XMFLOAT2 radius;
			//DirectX::XMStoreFloat3(&center, objectData.center);
			//DirectX::XMStoreFloat2(&radius, objectData.size);*/

			////配列に登録
			//objects.push_back(objWall);
		}

	}
}
