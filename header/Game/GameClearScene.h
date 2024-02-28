#pragma once
#include "header/Collider/CollisionManager.h"

#include "header/Engin/ViewProjection.h"
#include "header/Game/GameBaseScene.h"

#include "header/Game/BlackOut.h"
#include "header/Game/ClearSprite.h"

#include "header/3D/JsonLoader.h"

class Player;
class Platform;
class Gate;
class ClearBox;
class Rain;
class Floor;

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


	//�}�b�v�ǂݍ���
	void LoadMap();
private:
	ViewProjection* camera = nullptr;
	Input* input = nullptr;
	//�X�v���C�g�@�\
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	DirectXCommon* directXCom = DirectXCommon::GetInstance();
	//�Ó]
	BlackOut* blackOut = new BlackOut();
	ClearSprite* clearSprite = new ClearSprite();
	//����}�l�[�W���[
	CollisionManager* collisionManager = CollisionManager::GetInstance();
	//�I�u�W�F�N�g
	//�v���C���[
	Player* objPlayer = nullptr;
	//��
	Floor* objWall = {};
	//��
	Gate* objGate = {};
	//�N���A����p��
	ClearBox* objClearBox = nullptr;

	//�p�[�e�B�N��
	Rain* rain = nullptr;

	//�}�b�v�pJsonLoader
	//JSON
	LevelData* jsonLoader = nullptr;
	std::map<std::string, Model*> models;
	std::vector<Object3d*> objects;
};

