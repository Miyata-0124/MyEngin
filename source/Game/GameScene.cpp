#include "header/Game/GameScene.h"

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
	directXCom->Initialize(winApp);

	//FBX�֘A
	FbxLoader::GetInstance()->Initialize(directXCom->GetDevice());

	//�L�[���
	input = new	Input;
	input->Initialize(winApp);

	//�}�l�[�W������
	sceneManager = new GameSceneManager();

	//DirectX�����������@�@�����܂�
	//ViewProjection
	camera = new ViewProjection();
	camera->Initialeze();

	//�^�C�g���V�[��
	scene_ = new GameTitleScene();
	//�����V�[����ݒ肷��
	sceneManager->SetNextScene(scene_);
#pragma	endregion
	
}

void GameScene::Update()
{
	//�L�[���
	input->Update();
	//�J����
	camera->Update();

	sceneManager->Update(camera, input);
}

void GameScene::Draw()
{
	//�`�揈���������火
	directXCom->PreDraw();

	sceneManager->Draw();

	directXCom->PostDraw();
	//�����܂Ł�
}

void GameScene::Finalize()
{
	winApp->Finalize();
	sceneManager->~GameSceneManager();
	FbxLoader::GetInstance()->Finalize();
	delete input;
	delete winApp;
	delete model;
	//delete scene_;
	//delete object1;
	/*delete model1;
	delete obj3d;*/
}