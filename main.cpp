//自作クラス
#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "ViewProjection.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Particle.h"
#include "Object3d.h"
#include "Model.h"

using namespace DirectX;
using	namespace Microsoft::WRL;

//windowsアプリでのエントリーポイント(main関数)
int	WINAPI	WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#pragma	region	基盤システムの初期化
#pragma region WindowsAPIの初期化
	WinApp* winApp = nullptr;
	winApp = new	WinApp;
	winApp->Initialize();
#pragma endregion

#pragma region DirectX初期化処理
	//DirectX初期化処理　　ここから
	DirectXCommon* directXCom = nullptr;
	directXCom = new DirectXCommon;
	directXCom->Initialize(winApp);

	Input* input = nullptr;
	input = new	Input;
	input->Initialize(winApp);
	//DirectX初期化処理　　ここまで
#pragma endregion
#pragma	endregion
//スプライト
	SpriteCommon* spriteCommon = nullptr;
	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "testpar1.png");
	spriteCommon->Loadtexture(2, "test.png");
#pragma	region	シーンの初期化
	//ViewProjection
//	std::unique_ptr<ViewProjection>camera = std::make_unique<ViewProjection>();
//	camera->Initialeze();
//	//一度しか宣言しない
	Object3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	//スプライト
	Sprite* sprite = new Sprite();
	sprite->Initialize(spriteCommon, 1);
	sprite->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	sprite->SetSize(XMFLOAT2(1280.0f, 720.0f));
	sprite->SetPosition({ 640,360 });
//
//	Sprite* sprite2 = new Sprite();
//	sprite2->Initialize(spriteCommon, 2);
//	sprite2->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
//	sprite2->SetSize(XMFLOAT2(100.0f, 100.0f));
//	sprite2->SetPosition({ 50,50 });
//	//モデル
//	Model* model = Model::LoadFromOBJ("sphere");
//	Model* model2 = Model::LoadFromOBJ("wall");
//	//3dオブジェクト生成
//	Object3d* obj3d = Object3d::Create();
//	Object3d* obj3d2 = Object3d::Create();
//
//	//modelクラスをひも付け
//	obj3d->SetModel(model);
//	obj3d->SetSize({ 2,2,2 });
//	obj3d->SetPosition({ -15,0,0 });
//
//	obj3d2->SetModel(model2);
//	obj3d2->SetSize({ 2,2,2 });
//	obj3d2->SetPosition({ 15,0,0 });
//#pragma region パーティクル関係
//	//パーティクル
//	Particle::StaticInitialize(directXCom->GetDevice(), camera.get());
//	Particle::LoadTexture(1, "MK.png");
//	Particle::LoadTexture(2, "testpar1.png");
//	Particle* particle = nullptr;
//	// 引数の数字はテクスチャ読み込みのインデックスナンバー
//	particle = Particle::Create(1);
//	particle->Update();
#pragma	endregion
	//更新処理
	while (true)
	{

#pragma region メッセージ
		if (winApp->ProcessMessage()) {
			break;
		}
#pragma endregion

#pragma region 毎フレーム処理

		input->Update();
		//{
		//	XMFLOAT3 eye = camera->GetEye();
		//	XMFLOAT3 traget = camera->GetTarget();
		//	//eye.z -= 0.1f;

		//	camera->SetEye(eye);
		//	camera->Update();
		//}
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
		/*obj3d->Update();
		obj3d2->Update();
		particle->Update();*/
		//-------------------描画処理-------------------
		//Direct毎フレーム処理　ここから
		directXCom->PreDraw();
		/*Object3d::PreDraw(directXCom->GetCommandList());
		obj3d->Draw();
		obj3d2->Draw();

		Object3d::PostDraw();
		Particle::PreDraw(directXCom->GetCommandList());

		particle->Draw();

		Particle::PostDraw();*/

		sprite->SetIsInvisible(false);
		sprite->SetTexIndex(1);
		sprite->Draw();
		/*sprite2->SetTexIndex(2);
		sprite2->Draw();*/
		
		directXCom->PostDraw();

		//Direct毎フレーム処理　ここまで
#pragma endregion
		if (input->PushKey(DIK_ESCAPE))
		{
			break;
		}
	}
#pragma	region	最初のシーンの終了
	winApp->Finalize();
	delete input;
	delete winApp;
	delete directXCom;
	delete spriteCommon;
	delete sprite;
	//delete model;
	//delete model2;
	//delete obj3d;
#pragma	endregion
	return 0;
}