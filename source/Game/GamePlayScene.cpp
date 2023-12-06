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
	spriteCommon->Loadtexture(3, "Rule.png");
	//��x�����錾���Ȃ�
	Object3d::StaticInitialize(directXCom->GetDevice(), camera);
	//FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	Particle::StaticInitialize(directXCom->GetDevice(), camera);
	//�ڊo��
	wakeUp->Initialize(spriteCommon);

	blackOut->Initialize(spriteCommon);

	sprite->Initialize(spriteCommon, 3);
	//json�ǂݍ���
	jsonLoader = JsonLoader::LoadFlomJSONInternal("map");

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
	//�v���C���[���f��
	Model* playerModel = Model::LoadFromOBJ("player");
	Model* ground = Model::LoadFromOBJ("blue");
	//Model* item_ = Model::LoadFromOBJ("Item");
	Model* backGround = Model::LoadFromOBJ("BG");
#pragma endregion
#pragma region Player���̃I�u�W�F�N�g

	//�v���C���[
	objPlayer = Player::Create(playerModel);
	objPlayer -> SetInput(input);
	//�G
	//objEnem = Enemy::Create(ground);
	//�n��
	//objFloor = Floor::Create(item_);
	//�A�C�e��
	objItem = Item::Create(ground);
	objItem->SetInput(input);

	//�ړ��p�Q�[�g
	objGate = MoveGate::Create(backGround);
	objGate->SetInput(input);
	//�w�i
	//objBackGround = BackGround::Create(backGround);
#pragma endregion
	LoadMap();

#pragma region �p�[�e�B�N���֌W
	//rain = Rain::Create();
#pragma	endregion
}

void GamePlayScene::Finalize()
{
	//�I�u�W�F�N�g
	delete objPlayer;
	//delete objFloor;
	delete objItem;
	delete objBackGround;
	delete objGate;
	//delete rain;
	delete wakeUp;
	delete blackOut;
	delete sprite;
}

void GamePlayScene::Update()
{
	//�t�F�[�h�A�E�g
	wakeUp->Update();
	//�A�C�e��
	objItem->Update();
	//�v���C���[
	objPlayer->Update();
	//�n��
	//objFloor->Update();

	objGate->Update();
	//�w�i
	//objBackGround->Update();

	///JsonLoader�̍X�V
	for (auto object : objects) {
		object->Update();
	}

	//�J����
	camera->Update();

#pragma region �e�N���X�Ԃ̏��󂯓n��
	//�I�u�W�F�N�g
	//objEnem->SetPPosition(objPlayer->GetPosition());
	objPlayer->SetIsStop(objItem->GetIsStop());
	objItem->SetPPosition(objPlayer->GetPosition());
	objItem->SetRetention(objPlayer->GetRetention());
	objItem->SetDirection(objPlayer->GetDirection());
#pragma endregion
	//����}�l�[�W���[
	collisionManager->CheckAllCollisions();

	sprite->Update();

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
}

void GamePlayScene::Draw()
{
	Object3d::PreDraw(directXCom->GetCommandList());
	//�I�u�W�F�N�g
	//object1->Draw(directXCom->GetCommandList());

	//�v���C���[
	objPlayer->Draw();
	//�n��
	//objFloor->Draw();
	//��
	objGate->Draw();
	//�A�C�e��
	objItem->Draw();
	//�w�i
	//objBackGround->Draw();
	//JsonLoader�̕`��
	for (auto object : objects) {
		object->Draw();
	}
	Object3d::PostDraw();
	// UI,���o�֘A
	sprite->Draw();
	wakeUp->Draw();
	blackOut->Draw();
	
}

void GamePlayScene::LoadMap()
{
	for (auto& objectData : jsonLoader->objects) {
		Model* model_ = Model::LoadFromOBJ("wall");
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end()) { model_ = it->second; }

		//���f�����w�肵��3D�I�u�W�F�N�g�𐶐�
		Wall* objWall = Wall::Create();
		objWall->SetModel(model_);
		//���W
		DirectX::XMFLOAT3 scale;
		DirectX::XMStoreFloat3(&scale, objectData.scaling);
		objWall->SetScale(scale);

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
}
