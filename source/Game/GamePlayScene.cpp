#include "header/Game/GamePlayScene.h"
#include "header/Game/GameSceneManager.h"

#include "header/Collider/SphereCollider.h"
#include "header/Collider/PlaneCollider.h"
#include "header/Collider/BoxCollider.h"


#include "header/Game/Player.h"
#include "header/Game/enemy.h"
#include "header/Game/Floor.h"
#include "header/Game/Item.h"
#include "header/Game/Wall.h"
#include "header/Game/Gate.h"
#include "header/Game/StageGate.h"
#include "header/Game/Rain.h"
#include "header/Game/ClearBox.h"
#include "easing/Easing.h"

void GamePlayScene::Initialize(ViewProjection* camera_, Input* input_)
{
	//�X�v���C�g���ʕ����̏�����
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "taitle.png");
	spriteCommon->Loadtexture(2, "white1x1.png");
	spriteCommon->Loadtexture(3, "GameOver.png");
	spriteCommon->Loadtexture(4, "GameClear.png");

	//��x�����錾���Ȃ�
	Object3d::StaticInitialize(directXCom->GetDevice(), camera_);
	//FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	Particle::StaticInitialize(directXCom->GetDevice(), camera_);
	//�X�v���C�g
	
	//�N���A
	clearSprite->Initialize(spriteCommon);
	//�Q�[���I�[�o�[
	overSprite->Initialize(spriteCommon);
	//�Ó]
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
	//Model* pipe = Model::LoadFromOBJ("pipe");
	//Model* backGround = Model::LoadFromOBJ("BG");
	//Model* clear = Model::LoadFromOBJ("clear");
	//Model* gate = Model::LoadFromOBJ("gate");
#pragma endregion
#pragma region Player���̃I�u�W�F�N�g

	//�v���C���[
	objPlayer = Player::Create(playerModel);
	objPlayer -> SetInput(input_);
	//�G
	//objEnem = Enemy::Create(ground);
	objGate = StageGate::Create(ground);
	//�n��
	objFloor = Floor::Create(item_);

	/*for (int i = 0; i < 2; i++)
	{
		objGate[i] = Gate::Create(gate);
		objGate[i]->SetGateNum(i);
	}
	objGate[0]->SetPosition({ -25,-40,0 });
	objGate[1]->SetPosition({ -23, 40,0 });

	objClearBox = ClearBox::Create(clear);*/
	//�A�C�e��
	//objItem = Item::Create(ground);
	//objItem->SetInput(input);
	//��	
	//objWall = Wall::Create(ground);

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
	//�Q�[�����X�v���C�g
	delete clearSprite;
	delete overSprite;
	//���o
	delete blackOut;
	//�I�u�W�F�N�g
	delete objPlayer;
	delete objFloor;
	delete objGate;
	/*for (int i = 0; i < 2; i++)
	{
		delete objGate[i];
	}*/
	delete objClearBox;
	delete objItem;
	delete objBackGround;
	delete rain;


}

void GamePlayScene::Update()
{
	//if (input->TriggerKey(DIK_R))//���Z�b�g
	//{
	//	titleSprite->Reset();
	//	blackOut->Reset();
	//	scene = 0;
	//}

	////�t�F�[�h�A�E�g
	//blackOut->Update(scene, isBlackOut);
	//�v���C���[
	objPlayer->Update();
	//�G
	//objEnem->Update();
	//�A�C�e��
	//objItem -> Update();
	//�X�e�[�W�ړ��p
	objGate->Update();
	//�n��
	objFloor->Update();

	/*for (int i = 0; i < 2; i++)
	{
		objGate[i]->Update();
	}
	objClearBox->Update();*/
	//��
	//objWall->Update();
	//clearSprite->Update(objGate[1]->GetIsBlackOut());
	//�w�i
	//objBackGround->Update();

	///JsonLoader�̍X�V
	/*for (auto object : objects) {
		object->Update();
	}*/

#pragma region �e�N���X�Ԃ̏��󂯓n��
	//�I�u�W�F�N�g
	//objEnem->SetPPosition(objPlayer->GetPosition());
	/*objItem->SetPPosition(objPlayer->GetPosition());
	objItem->SetRetention(objPlayer->GetRetention());
	objItem->SetDirection(objPlayer->GetDirection());*/
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
	//�w�i

	//�I�u�W�F�N�g
	//object1->Draw(directXCom->GetCommandList());

	//�v���C���[
	objPlayer->Draw();
	//�G
	//objEnem->Draw();
	//�A�C�e��
	//objItem->Draw();
	objGate->Draw();
	//�n��
	objFloor->Draw();

	//�S�[���Q�[�g
	/*for (int i = 0; i < 2; i++)
	{
		objGate[i]->Draw();
	}
	objClearBox->Draw();*/
	//��
	//objWall->Draw();
	//�w�i
	//objBackGround->Draw();
	//
	/*for (auto object : objects) {
		object->Draw();
	}*/


	// UI,���o�֘A
	blackOut->Draw();
	clearSprite->Draw();
	Object3d::PostDraw();
}

