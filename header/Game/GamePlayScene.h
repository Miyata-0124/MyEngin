#pragma once
#include "header/Collider/CollisionManager.h"

#include "header/Game/BackGround.h"
#include "header/Game/BlackOut.h"
#include "header/Game/ClearSprite.h"
#include "header/Game/OverSprite.h"

class Player;
class BackGround;
class Floor;
class Item;
class Wall;
class Enemy;
class Rain;
class Gate;
class StageGate;
class ClearBox;

class GamePlayScene
{
public:// �����o�ϐ�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(ViewProjection* camera_ , Input* input_);

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:
	//�X�v���C�g�@�\
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	DirectXCommon* directXCom = DirectXCommon::GetInstance();
	
	ClearSprite* clearSprite = new ClearSprite();
	OverSprite* overSprite = new OverSprite();
	BlackOut* blackOut = new BlackOut();
	//����}�l�[�W���[
	CollisionManager* collisionManager = CollisionManager::GetInstance();
	//�Q�[�����I�u�W�F�N�g
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
	//�S�[���Q�[�g
	Gate* objGoalGate[2] = {};
	StageGate* objGate = nullptr;
	ClearBox* objClearBox = nullptr;
	//�w�i
	BackGround* objBackGround = nullptr;
	//�p�[�e�B�N��
	Rain* rain = nullptr;

};

