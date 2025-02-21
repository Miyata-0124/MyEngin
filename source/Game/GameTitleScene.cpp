#include "header/Game/GameTitleScene.h"
#include "header/Game/GameSceneManager.h"

void GameTitleScene::Initialize(ViewProjection* camera_,Input* input_)
{
	camera = camera_;
	input = input_;
	//キー情報
	input = input_;
	//スプライト共通部分の初期化
	spriteCommon->Initialize(directXCom);
	//spriteCommon->Loadtexture(1, "fileName.png");
	//一度だけ宣言する
	//Particle::StaticInitialize(directXCom->GetDevice(), camera_);

}

void GameTitleScene::Finalize()
{
	
}

void GameTitleScene::Update()
{
	
}

void GameTitleScene::Draw()
{
	
}
