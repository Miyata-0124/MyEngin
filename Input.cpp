#include "Input.h"
#include <cassert>


#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

Input* Input::GetInstance()
{
	static Input instance;
	return &instance;
}

void Input::Initialize(WinApp* winApp)
{
	HRESULT result;
	this->winApp = winApp;
	//DirectInputのインスタンス生成
	result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//キーボードデバイスの生成
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));
	//入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);//標準形式
	assert(SUCCEEDED(result));
	//排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

}

void Input::Update()
{
#pragma region キーボード
	// 前のキー情報保存
	memcpy(keyPre, key, sizeof(key));

	// キーボード情報の取得開始
	keyboard->Acquire();
	// 全キーの入力状態を取得する
	keyboard->GetDeviceState(sizeof(key), key);
#pragma endregion
}

bool Input::PushKey(BYTE keyNumber)
{
	// 指定キーを入力していればtrueを返す
	if (key[keyNumber]) {
		return true;
	}
	// それ以外でfalse
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	// トリガー判定　前で押していない&&今押している
	if (key[keyNumber] && !keyPre[keyNumber])
	{
		return true;
	}
	// それ以外でfalse
	return false;
}
