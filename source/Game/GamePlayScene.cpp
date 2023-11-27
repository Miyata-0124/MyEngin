#include "header/Game/GamePlayScene.h"
#include "header/Game/GameSceneManager.h"

#include "header/Game/Player.h"
#include "header/Game/enemy.h"
#include "header/Game/Floor.h"
#include "header/Game/Item.h"
#include "header/Game/Wall.h"
#include "header/Game/MoveGate.h"
#include "header/Game/Rain.h"
#include "easing/Easing.h"

#include "header/Game/GameClearScene.h"

void GamePlayScene::Initialize(ViewProjection* camera_, Input* input_)
{
	camera = camera_;
	input = input_;

	//�X�v���C�g���ʕ����̏�����
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "white1x1.png");
	spriteCommon->Loadtexture(2, "white1x1.png");
	//��x�����錾���Ȃ�
	Object3d::StaticInitialize(directXCom->GetDevice(), camera);
	//FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	Particle::StaticInitialize(directXCom->GetDevice(), camera);
	//�ڊo��
	wakeUp->Initialize(spriteCommon);

	blackOut->Initialize(spriteCommon);
	//jsonLoader = JsonLoader::LoadFlomJSONInternal("map");

#pragma region FBX
	/*model = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

	object1->initialize();
	object1->SetModel(model);
	object1->SetRotation({ 0,60,0 });
	object1->SetPosition({ 0,-3,0 });
	object1->PlayAnimation();*/
#pragma endregion
#pragma region ���f��
	//	//���f��
	//Model* model1 = Model::LoadFromOBJ("wall");
	//�v���C���[���f��
	Model* playerModel = Model::LoadFromOBJ("player");
	Model* ground = Model::LoadFromOBJ("blue");
	Model* item_ = Model::LoadFromOBJ("Item");
	Model* wall = Model::LoadFromOBJ("wall");
	//Model* pipe = Model::LoadFromOBJ("pipe");
	//Model* backGround = Model::LoadFromOBJ("BG");
	//Model* clear = Model::LoadFromOBJ("clear");
#pragma endregion
#pragma region Player���̃I�u�W�F�N�g

	//�v���C���[
	objPlayer = Player::Create(playerModel);
	objPlayer -> SetInput(input);
	//�G
	//objEnem = Enemy::Create(ground);
	//�n��
	objFloor = Floor::Create(item_);
	//��	
	objWall = Wall::Create(wall);
	//�A�C�e��
	objItem = Item::Create(ground);
	objItem->SetInput(input);

	//�ړ��p�Q�[�g
	objGate = MoveGate::Create(wall);
	objGate->SetInput(input);
	//�w�i
	//objBackGround = BackGround::Create(backGround);
#pragma endregion
	//LoadMap();

#pragma region �p�[�e�B�N���֌W
	rain = Rain::Create();
#pragma	endregion
}

void GamePlayScene::Finalize()
{
	//�I�u�W�F�N�g
	delete objPlayer;
	delete objFloor;
	/*for (int i = 0; i < 2; i++)
	{
		delete objGate[i];
	}*/
	delete objWall;
	delete objItem;
	delete objBackGround;
	delete objGate;
	delete rain;
	delete wakeUp;
	delete blackOut;
}

void GamePlayScene::Update()
{
		//�t�F�[�h�A�E�g
		wakeUp->Update();
		if (objGate->GetMapMove())
		{
			blackOut->Update();
			if (blackOut->GetMinAlpha() > blackOut->GetMaxAlpha())
			{
				objPlayer->SetPosition({ -20,-13,0 });
				objGate->SetMapMove(false);
				blackOut->Reset();
			}
		}

		//��
		objWall->Update();
		//�A�C�e��
		objItem->Update();

		if (objGate->GetMapMove())
		{
			blackOut->Update();
			if (blackOut->GetMinAlpha() > blackOut->GetMaxAlpha())
			{
				objGate->SetMapMove(false);
				objPlayer->SetPosition({ -20,-13,0 });
				blackOut->Reset();

				GameBaseScene* scene = new GameClearScene();
				sceneManager->SetNextScene(scene);
			}
		}
	
	//�v���C���[
	objPlayer->Update();
	//�n��
	objFloor->Update();

	objGate->Update();
	//�w�i
	//objBackGround->Update();

	///JsonLoader�̍X�V
	/*for (auto object : objects) {
		object->Update();
	}*/

	//�J����
	camera->Update();

#pragma region �e�N���X�Ԃ̏��󂯓n��
	//�I�u�W�F�N�g
	//objEnem->SetPPosition(objPlayer->GetPosition());
	objItem->SetPPosition(objPlayer->GetPosition());
	objItem->SetRetention(objPlayer->GetRetention());
	objItem->SetDirection(objPlayer->GetDirection());
	/*for (int i = 0; i < 2; i++) {
		objGate[i]->SetIsGoal(objClearBox->GetIsGoal());
	}
	blackOut->SetIsGoal(objGate[1]->GetIsBlackOut());*/
#pragma endregion
	//����}�l�[�W���[
	collisionManager->CheckAllCollisions();
}

void GamePlayScene::Draw()
{
	Object3d::PreDraw(directXCom->GetCommandList());
	//�I�u�W�F�N�g
	//object1->Draw(directXCom->GetCommandList());

	//�v���C���[
	objPlayer->Draw();
	//�n��
	objFloor->Draw();
	//��
	objGate->Draw();
	//��
	objWall->Draw();
	//�A�C�e��
	objItem->Draw();
	//�w�i
	//objBackGround->Draw();
	//JsonLoader�̕`��
	/*for (auto object : objects) {
		object->Draw();
	}*/
	Object3d::PostDraw();
	// UI,���o�֘A
	wakeUp->Draw();
	blackOut->Draw();
	
}

