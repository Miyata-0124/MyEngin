
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <vector>
#include <DirectXMath.h>
#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Sprite.h"
using namespace DirectX;
#define DIRECTINPUT_VERSION 0x0800 //DirectInputのバージョン指定
#include <dinput.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

//ウィンドウプロシージャ
LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	//メッセージに応じて固有の処理を行う
	switch (msg) {
		//ウィンドウが破棄された
	case WM_DESTROY:
		//OSに対して,アプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}

	//標準のメッセージを行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

//Windowsアプリでのエントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//コンソールへの文字出力
	OutputDebugStringA("Hello,Directx!!\n");
	WinApp* winApp = nullptr;
	// WindowsAPIの初期化
	winApp = new WinApp();
	winApp->Initialize();

	//DirectX初期化処理ここから
#pragma region 初期化DirectX
	DirectXCommon* dxCommon = nullptr;
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	Input* input = nullptr;
	input = new Input();
	input->Initialize(winApp);
#pragma endregion
	//DirectX初期化処理ここまで

	SpriteCommon* spriteCommon = nullptr;
	spriteCommon = new SpriteCommon();
	spriteCommon->Initialize(dxCommon);
	//描画初期化処理
	Sprite* sprite = new Sprite();
	sprite->Initialize(spriteCommon);
	//ゲームループ
	while (true)
	{
		//メッセージ処理
		if (winApp->ProcessMessage()) {
			//ゲームループを抜ける
			break;
		}

		//DirectX毎フレーム処理　ここから
		input->Update();
		sprite->Update();

		//描画前処理
		dxCommon->PreDraw();

		sprite->Draw();

		//描画後処理
		dxCommon->PostDraw();
		//DirectX枚フレーム処理　ここまで
	}
	
	winApp->Finalize();
	delete winApp;
	winApp = nullptr;
	delete dxCommon;
	dxCommon = nullptr;
	delete input;
	input = nullptr;
	delete spriteCommon;
	spriteCommon = nullptr;
	delete sprite;
	sprite = nullptr;
	return 0;
}