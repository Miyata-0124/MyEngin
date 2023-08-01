#include "Framework.h"

void Framework::Initialize()
{
#pragma region WindowsAPI‚Ì‰Šú‰»
	winApp = new	WinApp;
	winApp->Initialize();
#pragma endregion

#pragma region DirectX‰Šú‰»ˆ—
	//DirectX‰Šú‰»ˆ—@@‚±‚±‚©‚ç
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

//‘S‚Ä‚ð‚Ü‚Æ‚ß‚é•¨
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
