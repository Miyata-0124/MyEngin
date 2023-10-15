/**
 * @file Input.h
 * @brief キーボード情報機能をまとめた物
 * @author ミヤタ_コウキ
 * @date 2022/04/25
 */

#pragma once
#include <Windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION 0x0800 // DirectInputのバージョン指定
#include <dinput.h>
#include "WinApp.h"

class Input
{
public: // メンバ関数
	static Input* GetInstance();

	// 初期化
	void Initialize(WinApp* winApp);
	// 更新
	void Update();
	/// <summary>
	/// キーの押下をチェック
	/// </summary>
	/// <param name="keyNumber">キー番号(DIK_0等)</param>
	/// <returns>押されているか</returns>
	bool PushKey(BYTE keyNumber);
	/// <summary>
	/// トリガーキーをチェック
	/// </summary>
	/// <param name="keyNumber"></param>
	/// <returns></returns>
	bool TriggerKey(BYTE keyNumber);
	// namespace省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

private: // メンバ変数
	ComPtr<IDirectInput8> directInput;
	ComPtr<IDirectInputDevice8> keyboard;
	BYTE key[256] = {};		// キー情報
	BYTE keyPre[256] = {};	// 前キー情報
	//WinDowsAPI
	WinApp* winApp = nullptr;
};

