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
	sprite->Initialize(spriteCommon, 1);
	sprite->SetAnchorPoint(XMFLOAT2(0, 0));
	sprite->SetSize(XMFLOAT2(WinApp::window_width, WinApp::window_height));
	sprite->SetPosition({0,0});

	jsonLoader = JsonLoader::LoadFlomJSONInternal("test");

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
	Model* playerModel = Model::LoadFromOBJ("Box");
	Model* ground = Model::LoadFromOBJ("blue");
	Model* item_ = Model::LoadFromOBJ("Item");
	Model* backGround = Model::LoadFromOBJ("BG");
#pragma endregion
#pragma region Player���̃I�u�W�F�N�g

	collisionManager = CollisionManager::GetInstance();
	//�v���C���[
	objPlayer = Player::Create(ground);
	objPlayer->SetInput(input);
	//�G
	//objEnem = Enemy::Create(item_);
	//�n��
	objFloor = Floor::Create(playerModel);
	//�A�C�e��
	objItem = Item::Create(playerModel);
	objItem->SetInput(input);
	//��
	objWall = Wall::Create(item_);
	//�w�i
	objBackGround = BackGround::Create(backGround);
#pragma endregion
	LoadMap();
	
	#pragma region �p�[�e�B�N���֌W
	//	�p�[�e�B�N��
	Particle::LoadTexture(1, "blue1x1.png");
	//�����̐����̓e�N�X�`���ǂݍ��݂̃C���f�b�N�X�i���o�[
	particle = Particle::Create(1);
	#pragma	endregion
}

void GameScene::Update()
{
	//�L�[���
	input->Update();
	//�J����
	camera->Update();

	switch (scene)
	{
	case 0: //�^�C�g����� �J���~���Ă���悤�Ɍ�����^�C�g��
#pragma region �p�[�e�B�N��
		if (rainTimer < 10)
		{
			rainTimer++;
		}
		else
		{
			rainTimer = 0;
		}
		//�J�̊��
		if (rainTimer < 10)
		{
			//�p�[�e�B�N��
			for (int i = 0; i < 15; i++)
			{
				//XYZ�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
				//const	float	rnd_vel = 1.5f;
				XMFLOAT3	vel{};
				//vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

				//�d�͂Ɍ����Ă�Y�̂�[-0.001f,0]�Ń����_���ɕ��z
				const	float	rnd_acc = -0.1f;
				XMFLOAT3	acc{};
				acc.y = (float)rand() / RAND_MAX * rnd_acc;

				particle->Control(75, { (float)rand() / RAND_MAX * 100.0f - 100.0f / 2.0f,40,0}, vel, acc, 1.0f, 0.0f);
			}
		}
		particle->Update();
#pragma endregion
#pragma region �V�[���؂�ւ����̏���
		//���������߂ɍ��W���擾
		XMFLOAT2 position = sprite->GetPosition();
		if (!UIFlag) {
			if (position.x < 15)
			{
				UIspeed.x = 0.4f;
			}
			else
			{
				UIFlag = true;
			}
		}
		else
		{
			if (position.x > -15)
			{
				UIspeed.x = -0.4f;
			}
			else
			{
				UIFlag=false;
			}
		}
		position.x += UIspeed.x;
		position.y += UIspeed.y;

		//�؂�ւ�
		if (input->TriggerKey(DIK_SPACE) && !ChengeScene)
		{
			ChengeScene = true;
		}
		if (ChengeScene)
		{
			min += 0.1f;;
			y = min / max;
			position.y = startY + (endY - startY) * Easing::easeInSine(y);

			if (min>max)
			{
				min = 0.0f;
				ChengeScene = false;
				scene = 1;
			}
		}
		//�ړ���̍��W������
		sprite->SetPosition(position);

#pragma endregion
		break;
	case 1:
		//�v���C���[
		objPlayer->Update();
		//�G
		//objEnem->Update();
		//�A�C�e��
		objItem -> Update();
		//�n��
		objFloor -> Update();
		//��
		objWall -> Update();
		
		//�w�i
		objBackGround->Update();
		//obj3d->Update();
		

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

		//�����X�v���C�g�ړ�
#pragma region  �X�v���C�g�̈ړ����o
		////���������߂ɍ��W���擾
		//XMFLOAT2 position = sprite->GetPosition();
		////�ړ���̍��W������
		//sprite->SetPosition(position);
#pragma endregion
		
		break;
	case 2:
		break;
	}
	
}

void GameScene::Draw()
{
	//�`�揈���������火
	directXCom->PreDraw();
	Object3d::PreDraw(directXCom->GetCommandList());
	
	switch (scene)
	{
	case 0:
		sprite->SetIsInvisible(false);
		sprite->SetTexIndex(1);
		sprite->Draw();

		Particle::PreDraw(directXCom->GetCommandList());
		particle->Draw();
		Particle::PostDraw();

		break;
	case 1:
		
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
		objWall->Draw();
		//�w�i
		objBackGround->Draw();
		for (auto object : objects) {
			object->Draw();
		}

	
	// UI�֘A
		sprite->SetIsInvisible(false);
		sprite->SetTexIndex(2);
		sprite->SetSize({320, 180});
		sprite->SetPosition({ -320,0 });
		sprite->Draw();

		break;
	case 2:
		break;
	}
	
	Object3d::PostDraw();
	
	directXCom->PostDraw();
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
	delete sprite;
	delete model;
	delete objPlayer;
	delete objFloor;
	delete objItem;
	delete objBackGround;
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
		//DirectX::XMFLOAT3 center;
		// �z��ɓo�^
		objects.push_back(mapObject);
	}
}
