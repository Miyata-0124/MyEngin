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
	//DirectInput�̃C���X�^���X����
	result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//�L�[�{�[�h�f�o�C�X�̐���
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));
	//���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);//�W���`��
	assert(SUCCEEDED(result));
	//�r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

}

void Input::Update()
{
#pragma region �L�[�{�[�h
	// �O�̃L�[���ۑ�
	memcpy(keyPre, key, sizeof(key));

	// �L�[�{�[�h���̎擾�J�n
	keyboard->Acquire();
	// �S�L�[�̓��͏�Ԃ��擾����
	keyboard->GetDeviceState(sizeof(key), key);
#pragma endregion
}

bool Input::PushKey(BYTE keyNumber)
{
	// �w��L�[����͂��Ă����true��Ԃ�
	if (key[keyNumber]) {
		return true;
	}
	// ����ȊO��false
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	// �g���K�[����@�O�ŉ����Ă��Ȃ�&&�������Ă���
	if (key[keyNumber] && !keyPre[keyNumber])
	{
		return true;
	}
	// ����ȊO��false
	return false;
}
