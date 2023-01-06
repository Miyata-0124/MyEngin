
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
#define DIRECTINPUT_VERSION 0x0800 //DirectInput�̃o�[�W�����w��
#include <dinput.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

//�E�B���h�E�v���V�[�W��
LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	//���b�Z�[�W�ɉ����ČŗL�̏������s��
	switch (msg) {
		//�E�B���h�E���j�����ꂽ
	case WM_DESTROY:
		//OS�ɑ΂���,�A�v���̏I����`����
		PostQuitMessage(0);
		return 0;
	}

	//�W���̃��b�Z�[�W���s��
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

//Windows�A�v���ł̃G���g���[�|�C���g
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//�R���\�[���ւ̕����o��
	OutputDebugStringA("Hello,Directx!!\n");
	WinApp* winApp = nullptr;
	// WindowsAPI�̏�����
	winApp = new WinApp();
	winApp->Initialize();

	//DirectX������������������
#pragma region ������DirectX
	DirectXCommon* dxCommon = nullptr;
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	Input* input = nullptr;
	input = new Input();
	input->Initialize(winApp);
#pragma endregion
	//DirectX���������������܂�

	SpriteCommon* spriteCommon = nullptr;
	spriteCommon = new SpriteCommon();
	spriteCommon->Initialize(dxCommon);
	//�`�揉��������
	Sprite* sprite = new Sprite();
	sprite->Initialize(spriteCommon);
	//�Q�[�����[�v
	while (true)
	{
		//���b�Z�[�W����
		if (winApp->ProcessMessage()) {
			//�Q�[�����[�v�𔲂���
			break;
		}

		//DirectX���t���[�������@��������
		input->Update();
		sprite->Update();

		//�`��O����
		dxCommon->PreDraw();

		sprite->Draw();

		//�`��㏈��
		dxCommon->PostDraw();
		//DirectX���t���[�������@�����܂�
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