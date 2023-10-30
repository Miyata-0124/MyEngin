#include "header/Game/GameScene.h"
#include "header/Collider/SphereCollider.h"
#include "header/Collider/PlaneCollider.h"
#include "header/Collider/BoxCollider.h"
#include "header/Collider/CollisionManager.h"
#include "header/Game/Player.h"
#include "header/Game/enemy.h"
#include "header/Game/Floor.h"
#include "header/Game/Item.h"
#include "header/Game/Wall.h"
#include "header/Game/Rain.h"
#include "easing/Easing.h"
#include <sstream>
#include <iomanip>



void GameScene::Initialize()
{
#pragma region WindowsAPI�̏�����
	winApp = new WinApp;
	winApp->Initialize();
#pragma endregion

#pragma region DirectX����������
	//DirectX�����������@�@��������
	directXCom = new DirectXCommon;
	directXCom->Initialize(winApp);

	//FBX�֘A
	FbxLoader::GetInstance()->Initialize(directXCom->GetDevice());

	//�L�[���
	input = new	Input;
	input->Initialize(winApp);

	//DirectX�����������@�@�����܂�
#pragma	endregion
	//�X�v���C�g���ʕ����̏�����
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "taitle.png");
	spriteCommon->Loadtexture(2, "white1x1.png");
	//ViewProjection
	camera = new ViewProjection();
	camera->Initialeze();
//��x�����錾���Ȃ�
	Object3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	Particle::StaticInitialize(directXCom->GetDevice(),camera);
	//�X�v���C�g
	//�^�C�g��
	titleSprite->Initialize(spriteCommon);
	//�Ó]
	blackOut->Initialize(spriteCommon);

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
	//Model* model1 = Model::LoadFromOBJ("wall");
	//�v���C���[���f��
	Model* playerModel = Model::LoadFromOBJ("player");
	Model* ground = Model::LoadFromOBJ("blue");
	Model* item_ = Model::LoadFromOBJ("Item");
	Model* backGround = Model::LoadFromOBJ("BG");
#pragma endregion
#pragma region Player���̃I�u�W�F�N�g

	collisionManager = CollisionManager::GetInstance();
	//�v���C���[
	objPlayer = Player::Create(playerModel);
	objPlayer->SetInput(input);
	//�G
	//objEnem = Enemy::Create(item_);
	//�n��
	objFloor = Floor::Create(playerModel);
	//�A�C�e��
	objItem = Item::Create(item_);
	objItem->SetInput(input);
	//��
	objWall = Wall::Create(ground);
	//�w�i
	objBackGround = BackGround::Create(backGround);
#pragma endregion
	LoadMap();
	
	#pragma region �p�[�e�B�N���֌W
	rain = Rain::Create(1);
	#pragma	endregion
}

void GameScene::Update()
{
	//�L�[���
	input->Update();
	

	switch (scene)
	{
	case 0: //�^�C�g����� �J���~���Ă���悤�Ɍ�����^�C�g��
#pragma region �p�[�e�B�N��
		rain->Update();
#pragma endregion
#pragma region �V�[���؂�ւ����̏���
		

		titleSprite->Update(input,scene,isBlackOut);
		isBlackOut = titleSprite->GetBlackOut();

		//�Ó]������̂����f
		blackOut->Update(scene,isBlackOut);//�Ó]��V�[���؂�ւ�������
		scene = blackOut->GetScene();//�؂�ւ�������n��->�؂�ւ��

#pragma endregion
		break;
	case 1:
		if (input->TriggerKey(DIK_R))//���Z�b�g
		{
			titleSprite->Reset();
			blackOut->Reset();
			scene = 0;
		}

		//�t�F�[�h�A�E�g
		blackOut->Update(scene,isBlackOut);
		
		//�v���C���[
		objPlayer->Update();
		//�G
		//objEnem->Update();
		//�A�C�e��
		objItem -> Update();
		//�n��
		//objFloor -> Update();
		//��
		//objWall -> Update();
		
		//�w�i
		objBackGround->Update();
		

		for (auto object : objects) {
			object->Update();
		}

#pragma region �e�N���X�Ԃ̏��󂯓n��
		//�I�u�W�F�N�g
		//objEnem->SetPPosition(objPlayer->GetPosition());
		objItem->SetPPosition(objPlayer->GetPosition());
		objItem->SetRetention(objPlayer->GetRetention());
		objItem->SetDirection(objPlayer->GetDirection());
#pragma endregion
		//����}�l�[�W���[
		collisionManager->CheckAllCollisions();

		break;
	case 2:
		break;
	}

	//�J����
	camera->Update();
}

void GameScene::Draw()
{
	//�`�揈���������火
	directXCom->PreDraw();
	
	Particle::PreDraw(directXCom->GetCommandList());

	switch (scene)
	{
	case 0:
		
		//�^�C�g��
		titleSprite->Draw();

		rain->Draw();
		//�Ó]�p
		blackOut->Draw();

		
		break;

	case 1:
		Object3d::PreDraw(directXCom->GetCommandList());
		//�w�i
		
		//�I�u�W�F�N�g
		//object1->Draw(directXCom->GetCommandList());
		
		//�v���C���[
		objPlayer->Draw();
		//�G
		//objEnem->Draw();
		//�A�C�e��
		objItem->Draw();
		//�n��
		//objFloor->Draw();
		//��
		//objWall->Draw();
		//�w�i
		objBackGround->Draw();
		//
		for (auto object : objects) {
			object->Draw();
		}


		// UI,���o�֘A
		blackOut->Draw();
	
		Object3d::PostDraw();
		break;
	case 2:
		break;
	}

	directXCom->PostDraw();
	
	Particle::PostDraw();
	//�����܂Ł�
}

void GameScene::Finalize()
{
	winApp->Finalize();
	FbxLoader::GetInstance()->Finalize();
	delete input;
	delete winApp;
	delete directXCom;
	delete spriteCommon;
	delete titleSprite;
	delete blackOut;
	delete model;
	delete objPlayer;
	delete objFloor;
	delete objItem;
	delete objBackGround;
	delete rain;
	//delete object1;
	/*delete model1;
	delete obj3d;*/
}

void GameScene::LoadMap()
{
	for (auto& objectData : jsonLoader->objects) {
		Model* model_ = Model::LoadFromOBJ("TestBox");
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end()) { model_ = it->second; }

		// ���f�����w�肵��3D�I�u�W�F�N�g�𐶐�
		Object3d* mapObject = Object3d::Create();
		mapObject->SetModel(model_);
		// ���W
		DirectX::XMFLOAT3 scale;
		DirectX::XMStoreFloat3(&scale, objectData.scaling);
		mapObject->SetSize(scale);

		// ��]�p
		DirectX::XMFLOAT3 rot;
		DirectX::XMStoreFloat3(&rot, objectData.rotation);
		mapObject->SetRotation(rot);

		// ���W
		DirectX::XMFLOAT3 pos;
		DirectX::XMStoreFloat3(&pos, objectData.position);
		mapObject->SetPosition(pos);

		//�R���C�_�[
		DirectX::XMFLOAT3 center;
		DirectX::XMFLOAT2 radius;
		DirectX::XMStoreFloat3(&center, objectData.center);
		DirectX::XMStoreFloat2(&radius, objectData.size);

		mapObject->SetCollider(new BoxCollider({ center.x,center.y+radius.y/2,center.z }, { radius.x/2,radius.y/2 }));
		// �z��ɓo�^
		objects.push_back(mapObject);
	}
}
