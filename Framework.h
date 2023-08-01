#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"

class Framework
{
public:
	/// <summary>
	/// ������
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update();

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;;

	/// <summary>
	/// ���
	/// </summary>
	virtual void Finalize();

	virtual ~Framework() = default;

public:
	//���s
	void Run();
public: //main�Ɉꕔ�����n���p
	WinApp* GetWinApp() { return winApp; }
	DirectXCommon* GetDXCommon() { return directXCom; }
private:
	WinApp* winApp = nullptr;
	DirectXCommon* directXCom = nullptr;

};

