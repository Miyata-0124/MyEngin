#include "header/Game/GamePlayScene.h"
#include "header/Game/GameTitleScene.h"
#include "header/Game/GameSceneManager.h"

#include "header/3D/FbxObject3D.h"

#include "header/Game/Player.h"
#include "header/Game/enemy.h"
#include "header/Game/APBox.h"
#include "header/Game/Pipe.h"
#include "header/Game/Wall.h"
#include "header/Game/KeepsWall.h"
#include "header/Game/MoveGate.h"
#include "header/Game/Gate.h"
#include "header/Game/ClearBox.h"
#include "header/Game/Rain.h"
#include "easing/Easing.h"

void GamePlayScene::Initialize(ViewProjection* camera_, Input* input_)
{
	camera = camera_;
	input = input_;

	//�X�v���C�g���ʕ����̏�����
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "white1x1.png");
	spriteCommon->Loadtexture(2, "Rule.png");
	spriteCommon->Loadtexture(3, "sample.png");
	spriteCommon->Loadtexture(4, "ap.png");
	spriteCommon->Loadtexture(5, "noAP.png");
	//��x�����錾���Ȃ�
	Object3d::StaticInitialize(directXCom->GetDevice(), camera);
	FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	Particle::StaticInitialize(directXCom->GetDevice(), camera);
	//�ڊo��
	wakeUp = std::make_unique<WakeUp>();
	wakeUp->Initialize(spriteCommon);
	//�Ó]
	blackOut = std::make_unique<BlackOut>();
	blackOut->Initialize(spriteCommon);
	//AP
	ap = std::make_unique<AP>();
	ap->Initialize(spriteCommon);
	//�w�i
	back = std::make_unique<Sprite>();
	back->Initialize(spriteCommon, 3);
	back->SetSize({ 1280,720 });
	//json�ǂݍ���
	jsonLoader = JsonLoader::LoadFlomJSONInternal("map");
	//�}�b�v�ǂݍ���
	LoadMap();
#pragma region FBX
	//FbxModel* playerModel = FbxLoader::GetInstance()->LoadModelFromFile("player");
	/*

	object1->initialize();
	object1->SetModel(model);
	object1->SetRotation({ 0,60,0 });
	object1->SetPosition({ 0,-3,0 });
	object1->PlayAnimation();*/
#pragma endregion
#pragma region ���f��
	//	//���f��
	//�v���C���[���f��
	Model* playerModel = Model::LoadFromOBJ("sphere");
	//Model* ground = Model::LoadFromOBJ("blue");
	//Model* item_ = Model::LoadFromOBJ("Item");
#pragma endregion
#pragma region Player���̃I�u�W�F�N�g

	//�v���C���[
	objPlayer = Player::Create(playerModel);
	objPlayer -> SetInput(input);
	//�G
	//objEnem = Enemy::Create(ground);
	//�n��
	//objFloor = Floor::Create(item_);

	//�w�i
	//objBackGround = BackGround::Create(backGround);
#pragma endregion


#pragma region �p�[�e�B�N���֌W
	//rain = Rain::Create();
#pragma	endregion
}

void GamePlayScene::Finalize()
{
	//�I�u�W�F�N�g
	wakeUp.reset();
	blackOut.reset();
	ap.reset();
	back.reset();
	delete objPlayer;
	delete objBackGround;
	for (auto object : objects) {
		delete object;
	}
}

void GamePlayScene::Update()
{
	//�^�C�g���ɖ߂�
	/*GameBaseScene* scene = new GameTitleScene();
	sceneManager->SetNextScene(scene);*/
	
	//�t�F�[�h�A�E�g
	wakeUp->Update();
	//�v���C���[
	objPlayer->Update();
	//�n��
	//objFloor->Update();
	//�w�i
	//objBackGround->Update();

	///JsonLoader�̍X�V
	for (auto object : objects) {
		object->Update();
	}

	//�}�b�v�ړ�
	if (objClearBox->GetIsGoal() == true)
	{
		if (input->TriggerKey(DIK_V))
		{
			GameBaseScene* scene = new GameTitleScene();
			sceneManager->SetNextScene(scene);
		}
	}

	//�J����
	camera->Update();
	back->Update();

#pragma region �e�N���X�Ԃ̏��󂯓n��
	ap->SetAP(objPlayer->GetAP());
#pragma endregion
	//����}�l�[�W���[
	collisionManager->CheckAllCollisions();

	/*if (objGate->GetMapMove())
	{
		blackOut->Update();
		if (blackOut->GetMinAlpha() > blackOut->GetMaxAlpha())
		{
			objGate->SetMapMove(false);
			objPlayer->SetPosition({ -20,-13,0 });

			GameBaseScene* scene = new GameClearScene();
			sceneManager->SetNextScene(scene);
		}
	}*/
}

void GamePlayScene::Draw()
{
	back->Draw();
	Object3d::PreDraw(directXCom->GetCommandList());
	//�I�u�W�F�N�g
	//object1->Draw(directXCom->GetCommandList());

	//�v���C���[
	objPlayer->Draw();
	//JsonLoader�̕`��
	for (auto object : objects) {
		object->Draw();
	}
	Object3d::PostDraw();
	// UI,���o�֘A
	wakeUp->Draw();
	blackOut->Draw();
	ap->Draw();
	
}

void GamePlayScene::LoadMap()
{
	//�n�ʂɐڂ��Ă���ǃI�u�W�F�N�g
	Model* wall = Model::LoadFromOBJ("wall");
	Model* floor = Model::LoadFromOBJ("floor");
	Model* box = Model::LoadFromOBJ("box");
	Model* pipe = Model::LoadFromOBJ("pipe");
	Model* apBox = Model::LoadFromOBJ("apBox");
	//�N���A�͈�
	Model* clear = Model::LoadFromOBJ("clear");

	for (auto& objectData : jsonLoader->objects) {
		
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (objectData.fileName == "floor")
		{
			if (it != models.end()) { floor = it->second; }
			//���f�����w�肵��3D�I�u�W�F�N�g�𐶐�
			objWall = Floor::Create(floor);
			//�T�C�Y
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objWall->SetScale(scale);
			objWall->SetRadius({ scale.x,scale.y });

			//��]�p
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			objWall->SetRotation(rot);

			//���W
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.position);
			objWall->SetPosition(pos);

			//�R���C�_�[
			/*DirectX::XMFLOAT3 center;
			DirectX::XMFLOAT2 radius;
			DirectX::XMStoreFloat3(&center, objectData.center);
			DirectX::XMStoreFloat2(&radius, objectData.size);*/

			//�z��ɓo�^
			objects.push_back(objWall);
		}

		if (objectData.fileName == "wall")
		{
			if (it != models.end()) { wall = it->second; }
			//�ړ��p�Q�[�g
			objKeepsWall = Wall::Create(wall);
			//�T�C�Y
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objKeepsWall->SetScale(scale);
			objKeepsWall->SetRadius({ scale.x,scale.y });

			//��]�p
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			objKeepsWall->SetRotation(rot);

			//���W
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.position);
			objKeepsWall->SetPosition(pos);

			//���a���I�u�W�F�N�g�̃T�C�Y�ɍ��킹��
			objKeepsWall->SetRadius({ scale.x,scale.y });

			//�z��ɓo�^
			objects.push_back(objKeepsWall);
		}

		if (objectData.fileName == "item")
		{
			if (it != models.end()) { apBox = it->second; }
			//���f�����w�肵��3D�I�u�W�F�N�g�𐶐�
			objAP = APBox::Create(apBox);
			//�T�C�Y
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objAP->SetScale(scale);
			objAP->SetRadius({ scale.x,scale.y });

			//��]�p
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			objAP->SetRotation(rot);

			//���W
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.position);
			objAP->SetPosition(pos);

			//�z��ɓo�^
			objects.push_back(objAP);
		}

		if (objectData.fileName == "box")
		{
			if (it != models.end()) { box = it->second; }
			//���f�����w�肵��3D�I�u�W�F�N�g�𐶐�
			objWall = Floor::Create(box);
			//�T�C�Y
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objWall->SetScale(scale);
			objWall->SetRadius({ scale.x,scale.y });

			//��]�p
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			objWall->SetRotation(rot);

			//���W
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.position);
			objWall->SetPosition(pos);

			//�z��ɓo�^
			objects.push_back(objWall);
		}

		if (objectData.fileName == "pipe")
		{
			if (it != models.end()) { pipe = it->second; }
			//�ړ��p�Q�[�g
			objPipe = Pipe::Create(pipe);
			//�T�C�Y
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objPipe->SetScale(scale);
			objPipe->SetRadius({ scale.x,scale.y });

			//��]�p
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			objPipe->SetRotation(rot);

			//���W
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.position);
			objPipe->SetPosition(pos);

			//�z��ɓo�^
			objects.push_back(objPipe);
		}

		if (objectData.fileName == "goal")
		{
			if (it != models.end()) { clear = it->second; }
			//�ړ��p�Q�[�g
			objClearBox = ClearBox::Create(clear);
			//���W
			DirectX::XMFLOAT3 scale;
			DirectX::XMStoreFloat3(&scale, objectData.scaling);
			objClearBox->SetScale(scale);

			//��]�p
			DirectX::XMFLOAT3 rot;
			DirectX::XMStoreFloat3(&rot, objectData.rotation);
			objClearBox->SetRotation(rot);

			//���W
			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, objectData.position);
			objClearBox->SetPosition(pos);

			//�z��ɓo�^
			objects.push_back(objClearBox);
		}
	}
}
