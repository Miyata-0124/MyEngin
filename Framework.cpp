#include "Framework.h"

void Framework::Initialize()
{
#pragma region WindowsAPI�̏�����
	winApp = new	WinApp;
	winApp->Initialize();
#pragma endregion

#pragma region DirectX����������
	//DirectX�����������@�@��������
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

//�S�Ă��܂Ƃ߂镨
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
