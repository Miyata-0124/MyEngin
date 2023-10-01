#include "GameScene.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "Player.h"
#include "enemy.h"
#include "Floor.h"
#include "Item.h"
#include "Wall.h" 
#include <sstream>
#include <iomanip>

void GameScene::Initialize()
{
#pragma region WindowsAPI�̏�����
	winApp = new	WinApp;
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
#pragma endregion
#pragma	endregion
//�X�v���C�g
	//�X�v���C�g���ʕ����̏�����
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "MK.png");
	spriteCommon->Loadtexture(2, "test.png");
	//ViewProjection
	camera = new ViewProjection();
	camera->Initialeze();
//��x�����錾���Ȃ�
	Object3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	//Particle::StaticInitialize(directXCom->GetDevice(), camera.get());
	//�X�v���C�g
	sprite->Initialize(spriteCommon, 1);
	sprite->SetAnchorPoint(XMFLOAT2(0, 0));
	sprite->SetSize(XMFLOAT2(WinApp::window_width, WinApp::window_height));
	sprite->SetPosition({ -1280,0 });

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
	objEnem = Enemy::Create(ground);
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
		//�p�[�e�B�N��
		//Particle::LoadTexture(1, "MK.png");
		//Particle::LoadTexture(2, "testpar1.png");
		//Particle* particle = nullptr;
		//// �����̐����̓e�N�X�`���ǂݍ��݂̃C���f�b�N�X�i���o�[
		//particle = Particle::Create(1);
		//particle->Update();
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
	///���ꂼ��̃N���X��Update�̂݋L�q
	
	case 0:
		if (input->TriggerKey(DIK_SPACE))
		{
			scene = 1;	
		}
		break;
	case 1:
#pragma region �p�[�e�B�N��
		//�p�[�e�B�N������
		//if (input->TriggerKey(DIK_F))
		//{
		//	//�p�[�e�B�N��
		//	for (int i = 0; i < 100; i++)
		//	{
		//		//XYZ�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
		//		const	float	rnd_vel = 0.1f;
		//		XMFLOAT3	vel{};
		//		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		//		//�d�͂Ɍ����Ă�Y�̂�[-0.001f,0]�Ń����_���ɕ��z
		//		const	float	rnd_acc = 0.001f;
		//		XMFLOAT3	acc{};
		//		acc.y = (float)rand() / RAND_MAX * rnd_acc;

		//		particle->Control(100, obj3d->GetPosition(), vel, acc, 1.0f, 0.0f);
		//	}
		//}
#pragma endregion
#pragma region �X�v���C�g�ړ�
		/*{
			XMFLOAT2 position = sprite->GetPosition();
			if (input->PushKey(DIK_UP))
			{
				position.y -= 10.0f;
			}
			else if (input->PushKey(DIK_DOWN))
			{
				position.y += 10.0f;
			}
			if (input->PushKey(DIK_LEFT))
			{
				position.x -= 10.0f;
			}
			else if (input->PushKey(DIK_RIGHT))
			{
				position.x += 10.0f;

			}
			sprite->SetPosition(position);
		}*/
#pragma endregion
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
		//particle->Update();

		for (auto object : objects) {
			object->Update();
		}

#pragma region �e�N���X�Ԃ̏��󂯓n��
		//�I�u�W�F�N�g
		objEnem->SetPPosition(objPlayer->GetPosition());
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
	
}

void GameScene::Draw()
{
	//�`�揈���������火
	directXCom->PreDraw();
	switch (scene)
	{
	case 0:
		sprite->SetIsInvisible(false);
		sprite->SetTexIndex(1);
		sprite->Draw();
		break;
	case 1:
		//�w�i

		//�I�u�W�F�N�g
		//object1->Draw(directXCom->GetCommandList());
		Object3d::PreDraw(directXCom->GetCommandList());
		//�v���C���[
		objPlayer->Draw();
		//�G
		objEnem->Draw();
		//�A�C�e��
		objItem->Draw();
		//�n��
		objFloor->Draw();
		//��
		objWall->Draw();
		//�w�i
		objBackGround->Draw();
		for (auto object : objects) {
			object->Draw();
		}

		Object3d::PostDraw();
#pragma region �p�[�e�B�N��

		//Particle::PreDraw(directXCom->GetCommandList());
		//particle->Draw();
		//Particle::PostDraw();

#pragma endregion

	// UI�֘A
		sprite->SetIsInvisible(false);
		sprite->SetTexIndex(1);
		sprite->Draw();

		break;
	case 2:
		break;
	}
	
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
		Model* model = Model::LoadFromOBJ("Box");
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end()) { model = it->second; }

		//// ���f�����w�肵��3D�I�u�W�F�N�g�𐶐�
		//objBox = MapBox::Create(model);
		//// ���W
		//DirectX::XMFLOAT3 scale;
		//DirectX::XMStoreFloat3(&scale, objectData.scaling);
		//objBox->SetSize(scale);

		//// ��]�p
		//DirectX::XMFLOAT3 rot;
		//DirectX::XMStoreFloat3(&rot, objectData.rotation);
		//objBox->SetRotation(rot);

		//// ���W
		//DirectX::XMFLOAT3 pos;
		//DirectX::XMStoreFloat3(&pos, objectData.position);
		//objBox->SetPosition(pos);

		////�R���C�_�[
		////DirectX::XMFLOAT3 center;
		//// �z��ɓo�^
		//objects.push_back(objBox);
	}
}
