#pragma region before includer

//#include<string>
//#include <DirectXMath.h>
//#include<d3dcompiler.h>
//#include"DirectXTex/DirectXTex.h"
//#include<cassert>
//#include<vector>
//
//#pragma	comment(lib,"d3dcompiler.lib")
//#pragma	comment(lib, "d3d12.lib")
//#pragma	comment(lib,"dxgi.lib")
#pragma endregion
//自作クラス
#include"Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include"SpriteCommon.h"
#include"Sprite.h"
#include"Object3d.h"
#include"Model.h"

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
	spriteCommon->Loadtexture(1, "reimu.png");
	spriteCommon->Loadtexture(2, "test.png");
#pragma	region	最初のシーンの初期化
	//一度しか宣言しない
	Object3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	//スプライト
	Sprite* sprite = new Sprite();
	sprite->Initialize(spriteCommon, 1);
	sprite->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	sprite->SetSize(XMFLOAT2(100.0f, 100.0f));
	sprite->SetPosition({ 150,50 });

	Sprite* sprite2 = new Sprite();
	sprite2->Initialize(spriteCommon, 2);
	sprite2->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	sprite2->SetSize(XMFLOAT2(100.0f, 100.0f));
	sprite2->SetPosition({ 50,50 });
	//モデル
	Model* model = Model::LoadFromOBJ("sphere");
	Model* model2 = Model::LoadFromOBJ("wall");
	//3dオブジェクト生成
	Object3d* obj3d = Object3d::Create();
	Object3d* obj3d2 = Object3d::Create();
	//modelクラスをひも付け
	obj3d->SetModel(model);
	obj3d->SetSize({ 5,5,5 });
	obj3d->SetPosition({ -5,0,0 });

	obj3d2->SetModel(model2);
	obj3d2->SetSize({ 5,5,5 });
	obj3d2->SetPosition({ 5,0,0 });
	//変数
#pragma	endregion
	while (true)
	{

#pragma region メッセージ
		if (winApp->ProcessMessage()) {
			break;
		}
#pragma endregion

#pragma region 毎フレーム処理

		input->Update();

		//数字の0キーが押されてたら
		if (input->TriggerKey(DIK_0))
		{
			OutputDebugStringA("Hit 0\n");//出力ウィンドウに表示
		}
#pragma region スプライト移動
		{
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
		}
#pragma endregion
		obj3d->Update();
		obj3d2->Update();
		//-------------------描画処理-------------------
		//Direct毎フレーム処理　ここから
		directXCom->PreDraw();
		Object3d::PreDraw(directXCom->GetCommandList());
		obj3d->Draw();
		obj3d2->Draw();
		Object3d::PostDraw();

		//sprite->SetIsInvisible(true);
		sprite->SetTexIndex(1);
		sprite->Draw();
		sprite2->SetTexIndex(2);
		sprite2->Draw();
		//
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
	delete model;
	delete model2;
	delete obj3d;
#pragma	endregion
	return 0;
}