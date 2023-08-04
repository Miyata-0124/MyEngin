#pragma once
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Floor.h"
#include "Item.h"
#include "BackGround.h"
#include <sstream>
#include <iomanip>

class GamePlayScene
{
public:
	// ������
	void Initialize();

	// �I��
	void Finalize();

	// �X�V
	void Update();

	//�`��
	void Draw();

private:
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

