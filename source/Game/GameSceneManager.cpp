#include "header/Game/GameSceneManager.h"

void GameSceneManager::Update(ViewProjection* camera_, Input* input_)
{
	//�V�[���؂�ւ�����
	
	//��������Ȃ�
	if (nextScene) {
		//�Â��V�[�����I������
		if (scene) {
			scene->Finalize();
			delete scene;
		}

		//�؂�ւ�
		scene = nextScene;
		nextScene = nullptr;

		scene->SetScanManager(this);
		//���̃V�[���̏�����
		scene->Initialize(camera_, input_);
	}
	//�V�[���X�V
	scene->Update();
}

void GameSceneManager::Draw()
{
	scene->Draw();
}

GameSceneManager::~GameSceneManager()
{
	//�V�[���̏I��,���
	scene->Finalize();
	delete scene;
}
