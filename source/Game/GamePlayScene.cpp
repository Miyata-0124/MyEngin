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
	camera = camera_;
	input = input_;

	//�X�v���C�g���ʕ����̏�����
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "white1x1.png");

	//��x�����錾���Ȃ�
	Object3d::StaticInitialize(directXCom->GetDevice(), camera);
	//FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	Particle::StaticInitialize(directXCom->GetDevice(), camera);
	//�ڊo��
	wakeUp->Initialize(spriteCommon);

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
	//Model* gate = Model::LoadFromOBJ("gate");
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
	delete rain;
	delete wakeUp;

}

void GamePlayScene::Update()
{
	//�t�F�[�h�A�E�g
	wakeUp->Update();
	//�v���C���[
	objPlayer->Update();
	//�A�C�e��
	objItem -> Update();
	//�n��
	objFloor->Update();
	//��
	objWall->Update();
	//�w�i
	//objBackGround->Update();

	///JsonLoader�̍X�V
	/*for (auto object : objects) {
		object->Update();
	}*/

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
	//�w�i

	//�I�u�W�F�N�g
	//object1->Draw(directXCom->GetCommandList());

	//�v���C���[
	objPlayer->Draw();
	//�A�C�e��
	objItem->Draw();
	//�n��
	objFloor->Draw();
	//��
	objWall->Draw();
	//�w�i
	//objBackGround->Draw();
	//JsonLoader�̕`��
	/*for (auto object : objects) {
		object->Draw();
	}*/
	Object3d::PostDraw();
	// UI,���o�֘A
	wakeUp->Draw();
}

