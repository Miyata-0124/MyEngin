#pragma once
#include "header/Collider/CollisionManager.h"

#include "header/Game/GameBaseScene.h"
#include "header/Game/BackGround.h"
#include "header/Game/BlackOut.h"
#include "header/Game/WakeUp.h"
#include "header/3D/JsonLoader.h"

class Player;
class BackGround;
class Platform;
class Pipe;
class Item;
class Floor;
class Wall;
class Enemy;
class Rain;
class MoveGate;
class Gate;
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
	std::unique_ptr<WakeUp> wakeUp = nullptr;
	//�Ó]
	std::unique_ptr<BlackOut> blackOut = nullptr;
	std::unique_ptr<Sprite> back = nullptr;
	//����}�l�[�W���[
	CollisionManager* collisionManager = CollisionManager::GetInstance();
	//�Q�[�����I�u�W�F�N�g
	//�v���C���[
	Player* objPlayer = nullptr;
	//�G
	Enemy* objEnem = nullptr;
	//��(��)
	Platform* objFloor = nullptr;
	//�p�C�v
	Pipe* objPipe = nullptr;
	//��
	Floor* objWall = nullptr;
	//�v���C���[��ʂ��Ȃ���
	Wall* objKeepsWall = nullptr;
	//�A�C�e��
	Item* objItem = nullptr;
	//�N���A����p��
	ClearBox* objClearBox = nullptr;
	//�}�b�v�ړ��p�Q�[�g
	MoveGate* objMGate = nullptr;
	//��
	Gate* objGate = {};
	//�w�i
	BackGround* objBackGround = nullptr;
	//�p�[�e�B�N��
	//Rain* rain = nullptr;

	bool move = false;

	//�}�b�v�pJsonLoader
	//JSON
	LevelData* jsonLoader = nullptr;
	std::map<std::string, Model*> models;
	std::vector<Object3d*> objects;
};

