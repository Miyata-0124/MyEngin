#include "GamePlayScene.h"
#include "SpriteCommon.h"
#include "FbxObject3D.h"

void GamePlayScene::Initialize()
{
	SpriteCommon::GetInstance()->Loadtexture(1, "MK.png");
	SpriteCommon::GetInstance()->Loadtexture(2, "test.png");
	//ViewProjection
	/*camera = new ViewProjection();
	camera->Initialeze();*/
	//��x�����錾���Ȃ�
	Object3d::StaticInitialize(DirectXCommon::GetInstance()->GetDevice(), WinApp::window_width, WinApp::window_height);
	FbxObject3d::StaticInitialize(DirectXCommon::GetInstance()->GetDevice(), WinApp::window_width, WinApp::window_height);
	//Particle::StaticInitialize(directXCom->GetDevice(), camera.get());
	//�X�v���C�g
	sprite->Initialize(SpriteCommon::GetInstance(), 1);
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
	//�n��
	objFloor = Floor::Create(ground);
	//�A�C�e��
	objItem = Item::Create(item_);
	objItem->SetInput(input);
	//�w�i
	objBackGround = BackGround::Create(backGround);
#pragma endregion
	//LoadMap();

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

void GamePlayScene::Finalize()
{
}

void GamePlayScene::Update()
{
}

void GamePlayScene::Draw()
{
}
