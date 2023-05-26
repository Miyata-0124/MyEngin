#pragma once
//����N���X
#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "ViewProjection.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Particle.h"
#include "Object3d.h"
#include "Model.h"

using namespace DirectX;
using namespace Microsoft::WRL;

class GameScene
{
public: //��{�֐�
	void Initialize();
	void Update();
	void Draw();
	void Finalize();

public:
	WinApp* GetWinApp() { return winApp; }
	Input* GetInput() { return input; }

private: //�Q�[�����g�p�N���X
	WinApp* winApp = nullptr;
	DirectXCommon* directXCom = nullptr;
	Input* input = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Sprite* sprite = new Sprite();
};

