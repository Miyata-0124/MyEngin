#include "WinApp.h"

LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//メッセージで分岐
	switch (msg) {
	case WM_DESTROY: // ウィンドウが破棄された場合
		PostQuitMessage(0); // OSに対して,アプリの終了を伝える
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam); // 標準処理
}

WinApp* WinApp::GetInstance()
{
	static WinApp instance;
	return &instance;
}

void WinApp::Initialize()
{
	//ウィンドウクラスの設定
	windowOption.cbSize = sizeof(WNDCLASSEX);
	windowOption.lpfnWndProc = (WNDPROC)WindowProc;	 //ウィンドウプロシージャ設定
	windowOption.lpszClassName = L"DirectXGame";		 //ウィンドウクラス名
	windowOption.hInstance = GetModuleHandle(nullptr);	 //ウィンドウハンドル
	windowOption.hCursor = LoadCursor(NULL, IDC_ARROW); //カーソル指定

	//ウィンドウクラスをOSにする
	RegisterClassEx(&windowOption);
	//ウィンドウサイズ{ｘ座標,ｙ座標,横幅,立幅}
	RECT wrc = { 0,0,window_width,window_height };
	//自動でサイズを矯正する
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウオブジェクトの生成
		hwnd = CreateWindow(windowOption.lpszClassName,
		L"DirectXGame",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		windowOption.hInstance,
		nullptr);
	//ウィンドウを表示状態にする
	ShowWindow(hwnd, SW_SHOW);
}

void WinApp::Update()
{
}

void WinApp::Finalize()
{
	//ウィンドウクラスを登録解除
	UnregisterClass(windowOption.lpszClassName, windowOption.hInstance);
}

bool WinApp::ProcessMessage()
{
	//メッセージ
	MSG msg{};
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	if (msg.message == WM_QUIT)
	{
		return true;
	}
	return false;
}
