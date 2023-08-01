#pragma once
//����N���X
#include <list>
#include "Input.h"
#include "ViewProjection.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Particle.h"
#include "Object3d.h"
#include "FbxObject3D.h"
#include "FbxLoader.h"
#include "Model.h"
#include "JsonLoader.h"
#include "BackGround.h"
#include "Framework.h"

class CollisionManager;
class Player;
class BackGround;
class Floor;
class Item;

class GameScene : public Framework
{
public: //��{�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// ���
	/// </summary>
	void Finalize() override;

	void LoadMap();

public: //main�Ɉꕔ�����n���p
	Input* GetInput() { return input; }

private: //�Q�[�����g�p�N���X
	
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
	//��(��)
	Floor* objFloor = nullptr;
	//�A�C�e��
	Item* objItem = nullptr;
	//�w�i
	BackGround* objBackGround = nullptr;

	CollisionManager* collisionManager = nullptr;
};

