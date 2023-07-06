#include "GameScene.h"
#include "Collision.h"
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
#pragma	region	�V�[���̏�����
	//ViewProjection
	
//��x�����錾���Ȃ�
	Object3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	//Particle::StaticInitialize(directXCom->GetDevice(), camera.get());
	//�X�v���C�g
	sprite->Initialize(spriteCommon, 1);
	sprite->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	sprite->SetSize(XMFLOAT2(320.0f, 180.0f));
	sprite->SetPosition({ 160,90 });

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
#pragma endregion
#pragma region Player���̃I�u�W�F�N�g

	player->Initialize(playerModel);
	flor->Initialize(ground);

	//�@3d�I�u�W�F�N�g����
		/*Object3d* obj3d = Object3d::Create();
		model�N���X���Ђ��t��
		obj3d->SetModel(model1);
		obj3d->SetSize({ 2,2,2 });
		obj3d->SetPosition({ 15,0,0 });*/
#pragma endregion

	
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
	///���ꂼ��̃N���X��Update�̂݋L�q
	//�L�[���
	input->Update();
	
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
	player->Update(input,hit);
	flor->Update();

		//obj3d->Update();
		//particle->Update();

	//object1->Update();
	hit = Collision::CheckSphere2Plane(sphere, plane);
}

void GameScene::Draw()
{
	//�`�揈���������火
	directXCom->PreDraw();
	//�w�i


	//�I�u�W�F�N�g
	//object1->Draw(directXCom->GetCommandList());
	Object3d::PreDraw(directXCom->GetCommandList());
	player->Draw();
	flor->Draw();

	//obj3d->Draw();

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
	delete object1;
	delete player;
	/*delete model1;
	delete obj3d;*/
}
