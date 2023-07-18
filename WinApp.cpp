#include "WinApp.h"

LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//���b�Z�[�W�ŕ���
	switch (msg) {
	case WM_DESTROY: // �E�B���h�E���j�����ꂽ�ꍇ
		PostQuitMessage(0); // OS�ɑ΂���,�A�v���̏I����`����
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam); // �W������
}

WinApp* WinApp::GetInstance()
{
	static WinApp instance;
	return &instance;
}

void WinApp::Initialize()
{
	//�E�B���h�E�N���X�̐ݒ�
	windowOption.cbSize = sizeof(WNDCLASSEX);
	windowOption.lpfnWndProc = (WNDPROC)WindowProc;	 //�E�B���h�E�v���V�[�W���ݒ�
	windowOption.lpszClassName = L"DirectXGame";		 //�E�B���h�E�N���X��
	windowOption.hInstance = GetModuleHandle(nullptr);	 //�E�B���h�E�n���h��
	windowOption.hCursor = LoadCursor(NULL, IDC_ARROW); //�J�[�\���w��

	//�E�B���h�E�N���X��OS�ɂ���
	RegisterClassEx(&windowOption);
	//�E�B���h�E�T�C�Y{�����W,�����W,����,����}
	RECT wrc = { 0,0,window_width,window_height };
	//�����ŃT�C�Y����������
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//�E�B���h�E�I�u�W�F�N�g�̐���
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
	//�E�B���h�E��\����Ԃɂ���
	ShowWindow(hwnd, SW_SHOW);
}

void WinApp::Update()
{
}

void WinApp::Finalize()
{
	//�E�B���h�E�N���X��o�^����
	UnregisterClass(windowOption.lpszClassName, windowOption.hInstance);
}

bool WinApp::ProcessMessage()
{
	//���b�Z�[�W
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
