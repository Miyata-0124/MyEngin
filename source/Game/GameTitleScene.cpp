#include "header/Game/GameTitleScene.h"
#include "header/Game/GameSceneManager.h"

void GameTitleScene::Initialize(ViewProjection* camera_,Input* input_)
{
	//カメラ情報
	camera = camera_;
	//キー情報
	input = input_;
	//スプライト共通部分の初期化
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "black1x1.png");
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
