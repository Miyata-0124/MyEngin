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
#include "FbxObject3D.h"
#include "Model.h"
#include "FbxLoader.h"
#include "JsonLoader.h"
#include "PostEffect.h"

class GameScene
{
public: //��{�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���
	/// </summary>
	void Finalize();

	void LoadMapBox();
public: //main�Ɉꕔ�����n���p
	WinApp* GetWinApp() { return winApp; }
	Input* GetInput() { return input; }

private: //�Q�[�����g�p�N���X
	WinApp* winApp = nullptr;
	DirectXCommon* directXCom = nullptr;
	//�L�[���
	Input* input = nullptr;
	//�X�v���C�g
	SpriteCommon* spriteCommon = nullptr;
	Sprite* sprite = new Sprite();
	//�J����������
	std::unique_ptr<Camera>camera = std::make_unique<Camera>();
	//JSON
	LevelData* jsonLoader = nullptr;
	std::map<std::string, Model*> models;

	std::vector<Object3d*> objects;
	//�|�X�g�G�t�F�N�g
	PostEffect* postEffect = nullptr;
	//FBX
	FbxModel* model2 = nullptr;
	FbxObject3d* object1 = new FbxObject3d();
};