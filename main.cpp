#include <Windows.h>
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

	//ウィンドウサイズ
	const int window_width = 1200;//横
	const int window_height = 720;//縦

	//ウィンドウクラスの設定
	WNDCLASSEX w{};
	w.cbSize = sizeof(WNDCLASSEX);			
	w.lpfnWndProc = (WNDPROC)WindowProc;	 //ウィンドウプロシージャ設定
	w.lpszClassName = L"DirectXGame";		 //ウィンドウクラス名
	w.hInstance = GetModuleHandle(nullptr);	 //ウィンドウハンドル
	w.hCursor = LoadCursor(NULL, IDC_ARROW); //カーソル指定

	//ウィンドウクラスをOSにする
	RegisterClassEx(&w);
	//ウィンドウサイズ{ｘ座標,ｙ座標,横幅,立幅}
	RECT wrc = { 0,0,window_width,window_height };
	//自動でサイズを矯正する
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウオブジェクトの生成
	HWND  hwnd = CreateWindow(w.lpszClassName,
		L"DirectXGame",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wrc.right - wrc.left,
		wrc.bottom - wrc.top,
		nullptr,
		nullptr,
		w.hInstance,
		nullptr);
	//ウィンドウを表示状態にする
	ShowWindow(hwnd, SW_SHOW);

	MSG msg{};	//メッセージ

	//DirectX初期化処理ここから
	
	//DirectX初期化処理ここまで

	//ゲームループ
	while (true)
	{
		if (PeekMessage
		(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//×ボタンで終了メッセージが出たらループえお抜ける
		if (msg.message == WM_QUIT) {
			break;
		}
		//DirectX枚フレーム処理　ここから

		//DirectX枚フレーム処理　ここまで
	}
	//ウィンドウクラスを登録
	UnregisterClass(w.lpszClassName, w.hInstance);
	return 0;
}