/**
 * @file GameScene.h
 * @brief �Q�[���֘A�̊�� �����ɏ�������ł���
 * @author �~���^_�R�E�L
 * @date 2022/04/13
 */

#pragma once
//����N���X
#include <list>
#include "header/Engin/Input.h"
#include "header/Engin/WinApp.h"
#include "header//Engin/DirectXCommon.h"
#include "header/Engin/ViewProjection.h"
#include "header/2D/SpriteCommon.h"
#include "header/3D/Object3D.h"
#include "header/3D/FbxObject3D.h"
#include "header/3D/FbxModel.h"
#include "header/3D/Model.h"
#include "header/3D/JsonLoader.h"
//�V�[���֘A
#include "header/Game/GameSceneManager.h"
#include "header/Game/GameTitleScene.h"
#include "header/Game/GamePlayScene.h"

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

	void LoadMap();

public: //main�Ɉꕔ�����n���p
	WinApp* GetWinApp() { return winApp; }
	Input* GetInput() { return input; }

private: //�Q�[�����g�p�N���X
	WinApp* winApp = nullptr;
	DirectXCommon* directXCom = DirectXCommon::GetInstance();
	//�f�o�b�O�e�L�X�g
	//ImguiManager* imgui = nullptr;
	//�L�[���
	Input* input = nullptr;
	//�J����
	ViewProjection* camera = nullptr;
	
	//FBX
	FbxModel* model = nullptr;
	FbxObject3d* object1 = new FbxObject3d();
	
	//�V�[���}�l�[�W��
	GameSceneManager* sceneManager = nullptr;
	//�}�b�v�pJsonLoader
	//JSON
	LevelData* jsonLoader = nullptr;
	std::map<std::string, Model*> models;
	std::vector<Object3d*> objects;


	//�V�[���؂�ւ��v���
	int scene = 0;
	//�J���Ǘ����鎞�v
	float rainTimer = 0.0f;
	bool rainFlag = false;
	////UI�֘A
	bool isBlackOut = false;

	GameBaseScene* scene_ = nullptr;
};

