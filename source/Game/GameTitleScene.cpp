#include "header/Game/GameTitleScene.h"
#include "header/Game/Rain.h"

void GameTitleScene::Initialize(ViewProjection* camera_,Input* input_)
{
	//キー情報
	input = input_;
	//スプライト共通部分の初期化
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "taitle.png");
	//タイトル
	titleSprite->Initialize(spriteCommon);
	//一度だけ宣言する
	Particle::StaticInitialize(directXCom->GetDevice(), camera_);

#pragma region パーティクル関係
	rain = Rain::Create();
#pragma	endregion
}

void GameTitleScene::Finalize()
{
	//ゲーム内スプライト
	delete titleSprite;
	//雨
	delete rain;
}

void GameTitleScene::Update()
{
	#pragma region パーティクル
	rain->Update();
	#pragma endregion
	#pragma region シーン切り替え時の処理

	titleSprite->Update(input, 0);
}

void GameTitleScene::Draw()
{
	//タイトル
	titleSprite->Draw();

	Particle::PreDraw(directXCom->GetCommandList());
	rain->Draw();
	Particle::PostDraw();
}
