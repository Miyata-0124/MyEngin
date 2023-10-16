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
#include "header/2D/Sprite.h"
#include "header/2D/Particle.h"
#include "header/3D/Object3D.h"
#include "header/3D/FbxObject3D.h"
#include "header/3D/FbxModel.h"
#include "header/3D/Model.h"
#include "header/3D/JsonLoader.h"
#include "header/Game/BackGround.h"

class CollisionManager;
class Player;
class BackGround;
class Floor;
class Item;
class Wall;
class Enemy;

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
	DirectXCommon* directXCom = nullptr;
	//�f�o�b�O�e�L�X�g
	//ImguiManager* imgui = nullptr;
	//�L�[���
	Input* input = nullptr;
	//�J����
	ViewProjection* camera = nullptr;
	//�X�v���C�g
	SpriteCommon* spriteCommon = nullptr;
	Sprite* sprite = new Sprite();
	//FBX
	FbxModel* model = nullptr;
	FbxObject3d* object1 = new FbxObject3d();
	
	//�}�b�v�pJsonLoader
	//JSON
	LevelData* jsonLoader = nullptr;
	std::map<std::string, Model*> models;
	std::vector<Object3d*> objects;

	//�v���C���[
	Player* objPlayer = nullptr;
	//�G
	Enemy* objEnem = nullptr;
	//��(��)
	Floor* objFloor = nullptr;
	//�A�C�e��
	Item* objItem = nullptr;
	//��
	Wall* objWall = nullptr;
	//�w�i
	BackGround* objBackGround = nullptr;

	CollisionManager* collisionManager = nullptr;

	//�p�[�e�B�N��
	Particle* particle = nullptr;
	//�V�[���؂�ւ��v���
	int scene = 0;
	//�^�C�g���Ȃǂ�UI���
	bool ChengeScene = false;
	//�J���Ǘ����鎞�v
	float rainTimer = 0.0f;
	bool rainFlag = false;
	//UI�֘A
	bool UIFlag = false;
	DirectX::XMFLOAT2 UIspeed = { 0,0 };

	//�g�k�t���O
	//�Ó]
	float min = 0.0f;
	float max = 1.0f;
	float startY = 0.0f;
	float endY = 720.0f;
	float y;
};

