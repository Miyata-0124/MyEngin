/**
 * @file WinApp.h
 * @brief ウィンドウ機能をまとめた物
 * @author ミヤタ_コウキ
 * @date 2022/04/13
 */

#pragma once
#include <Windows.h>
class WinApp
{
public: // 静的メンバ関数
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public: // メンバ関数
	static WinApp* GetInstance();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 終了
	void Finalize();
	// メッセージの処理
	bool ProcessMessage();
	// getter
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return windowOption.hInstance; }
public: // 定数
	//ウィンドウサイズ
	static const int window_width = 1280;//横
	static const int window_height = 720;//縦
private:
	// ウィンドウハンドル
	HWND hwnd = nullptr;
	// ウィンドウクラスの設定
	WNDCLASSEX windowOption{};
};

