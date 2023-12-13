#pragma once
#include "header/Collider/CollisionManager.h"

#include "header/Game/GameBaseScene.h"
#include "header/Game/BackGround.h"
#include "header/Game/BlackOut.h"
#include "header/Game/WakeUp.h"
#include "header/3D/JsonLoader.h"

class Player;
class BackGround;
class Floor;
class Item;
class Wall;
class KeepsWall;
class Enemy;
class Rain;
class MoveGate;
class ClearBox;

class GamePlayScene : public GameBaseScene
{
public:// �����o�ϐ�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(ViewProjection* camera_, Input* input_) override;

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize()override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw()override;

	//�}�b�v�ǂݍ���
	void LoadMap();
private:
	ViewProjection* camera;
	Input* input;
private:
	//�X�v���C�g�@�\
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	DirectXCommon* directXCom = DirectXCommon::GetInstance();
	//�X�v���C�g
	//���o
	WakeUp* wakeUp = new WakeUp();
	//�Ó]
	BlackOut* blackOut = new BlackOut();
	Sprite* sprite = new Sprite();
	//����}�l�[�W���[
	CollisionManager* collisionManager = CollisionManager::GetInstance();
	//�Q�[�����I�u�W�F�N�g
	//�v���C���[
	Player* objPlayer = nullptr;
	//�G
	Enemy* objEnem = nullptr;
	//��(��)
	Floor* objFloor = nullptr;
	//��
	Wall* objWall = nullptr;
	//�v���C���[��ʂ��Ȃ���
	KeepsWall* objKeepsWall = nullptr;
	//�A�C�e��
	Item* objItem = nullptr;
	//�}�b�v�ړ��p�Q�[�g
	MoveGate* objGate = nullptr;
	//�w�i
	BackGround* objBackGround = nullptr;
	//�p�[�e�B�N��
	//Rain* rain = nullptr;

	XMFLOAT3 move = { 0,0,0 };

	//�}�b�v�pJsonLoader
	//JSON
	LevelData* jsonLoader = nullptr;
	std::map<std::string, Model*> models;
	std::vector<Object3d*> objects;
};

