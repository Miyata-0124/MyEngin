#pragma once
#include "header/Collider/CollisionManager.h"

#include "header/Engin/ViewProjection.h"
#include "header/Game/GameBaseScene.h"

#include "header/Game/BlackOut.h"

class Player;
class Floor;
class Gate;
class ClearBox;

class GameClearScene : public GameBaseScene
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(ViewProjection* camera_, Input* input_)override;

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
	ViewProjection* camera = nullptr;
	Input* input = nullptr;
	//�X�v���C�g�@�\
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	DirectXCommon* directXCom = DirectXCommon::GetInstance();
	//�Ó]
	BlackOut* blackOut = new BlackOut();
	//����}�l�[�W���[
	CollisionManager* collisionManager = CollisionManager::GetInstance();
	//�I�u�W�F�N�g
	//�v���C���[
	Player* objPlayer = nullptr;
	//��(��)
	Floor* objFloor[3] = {};
	//��
	Gate* objGate[2] = {};
	//�N���A����p��
	ClearBox* objClearBox = nullptr;
};

