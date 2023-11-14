#include "header/Game/GameSceneManager.h"

void GameSceneManager::Update(ViewProjection* camera_, Input* input_)
{
	//シーン切り替え処理
	
	//次があるなら
	if (nextScene) {
		//古いシーンを終了する
		if (scene) {
			scene->Finalize();
			delete scene;
		}

		//切り替え
		scene = nextScene;
		nextScene = nullptr;

		scene->SetScanManager(this);
		//次のシーンの初期化
		scene->Initialize(camera_, input_);
	}
	//シーン更新
	scene->Update();
}

void GameSceneManager::Draw()
{
	scene->Draw();
}

GameSceneManager::~GameSceneManager()
{
	//シーンの終了,解放
	scene->Finalize();
	delete scene;
}
