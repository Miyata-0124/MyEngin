#include "Framework.h"

void Framework::Initialize()
{
#pragma region WindowsAPIの初期化
	winApp = new	WinApp;
	winApp->Initialize();
#pragma endregion

#pragma region DirectX初期化処理
	//DirectX初期化処理　　ここから
	directXCom = new DirectXCommon;
	directXCom->Initialize(winApp);
}

void Framework::Update()
{
}

void Framework::Finalize()
{
	winApp->Finalize();
	delete winApp;
	delete directXCom;
}

//全てをまとめる物
void Framework::Run()
{
	Initialize();

	while (true)
	{
		Update();

		Draw();
	}

	Finalize();
}
