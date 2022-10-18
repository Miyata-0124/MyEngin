#pragma once
#include <Windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION 0x0800 // DirectInput�̃o�[�W�����w��
#include <dinput.h>

class Input
{
public: // �����o�֐�
	// ������
	void Initialize(HINSTANCE hInstance,HWND hwnd);
	// �X�V
	void Update();
	/// <summary>
	/// �L�[�̉������`�F�b�N
	/// </summary>
	/// <param name="keyNumber">�L�[�ԍ�(DIK_0��)</param>
	/// <returns>������Ă��邩</returns>
	bool PushKey(BYTE keyNumber);
	/// <summary>
	/// �g���K�[�L�[���`�F�b�N
	/// </summary>
	/// <param name="keyNumber"></param>
	/// <returns></returns>
	bool TriggerKey(BYTE keyNumber);
	// namespace�ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;

private: // �����o�ϐ�
	ComPtr<IDirectInput8> directInput;
	ComPtr<IDirectInputDevice8> keyboard;
	BYTE key[256] = {};		// �L�[���
	BYTE keyPre[256] = {};	// �O�L�[���
};

