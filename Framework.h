#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"

class Framework
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;;

	/// <summary>
	/// 解放
	/// </summary>
	virtual void Finalize();

	virtual ~Framework() = default;

public:
	//実行
	void Run();
public: //mainに一部引き渡し用
	WinApp* GetWinApp() { return winApp; }
	DirectXCommon* GetDXCommon() { return directXCom; }
private:
	WinApp* winApp = nullptr;
	DirectXCommon* directXCom = nullptr;

};

