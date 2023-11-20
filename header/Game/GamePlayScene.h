#pragma once
#include "header/Collider/CollisionManager.h"

#include "header/Game/GameBaseScene.h"
#include "header/Game/BackGround.h"
#include "header/Game/BlackOut.h"
#include "header/Game/WakeUp.h"

class Player;
class BackGround;
class Floor;
class Item;
class Wall;
class Enemy;
class Rain;
class MoveGate;
class ClearBox;

enum class MAP
{
	MAP1,
	MAP2,
};

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

private:
	ViewProjection* camera;
	Input* input;

	MAP map = MAP::MAP1;
private:
	//�X�v���C�g�@�\
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	DirectXCommon* directXCom = DirectXCommon::GetInstance();
	//�X�v���C�g
	//���o
	WakeUp* wakeUp = new WakeUp();
	//�Ó]
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
	//�}�b�v�ړ��p�Q�[�g
	MoveGate* objGate = nullptr;
	//�w�i
	BackGround* objBackGround = nullptr;
	//�p�[�e�B�N��
	Rain* rain = nullptr;

	XMFLOAT3 move = { 0,0,0 };
};

