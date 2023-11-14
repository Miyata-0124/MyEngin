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

//	switch (scene)
//	{
//	case 0: //�^�C�g����� �J���~���Ă���悤�Ɍ�����^�C�g��
////#pragma region �p�[�e�B�N��
////		rain->Update();
////#pragma endregion
////#pragma region �V�[���؂�ւ����̏���
////
////
////		titleSprite->Update(input, scene, isBlackOut);
////		isBlackOut = titleSprite->GetBlackOut();
////
////		//�Ó]������̂����f
////		blackOut->Update(scene, isBlackOut);//�Ó]��V�[���؂�ւ�������
////		scene = blackOut->GetScene();//�؂�ւ�������n��->�؂�ւ��
//
//#pragma endregion
//		break;
//	case 1:
//		
//
//		break;
//	case 2:
//		/*rain->Update();
//		overSprite->Update();*/
//		break;
//	}

}

void GameScene::Draw()
{
	//�`�揈���������火
	directXCom->PreDraw();

	sceneManager->Draw();

	directXCom->PostDraw();
	//�����܂Ł�

	//switch (scene)
	//{
	//case 0:
	//	
	//	//�^�C�g��
	//	//titleSprite->Draw();

	//	//rain->Draw();
	//	////�Ó]�p
	//	//blackOut->Draw();
	//	break;

	//case 1:

	//	break;
	//case 2:
	//	/*rain->Draw();
	//	overSprite->Draw();*/
	//	break;
	//}


}

void GameScene::Finalize()
{
	winApp->Finalize();
	sceneManager->~GameSceneManager();
	FbxLoader::GetInstance()->Finalize();
	delete input;
	delete winApp;
	delete model;
	
	//scene_->Finalize();
	//delete scene_;
	//delete object1;
	/*delete model1;
	delete obj3d;*/
}

//void GameScene::LoadMap()
//{
//	for (auto& objectData : jsonLoader->objects) {
//		Model* model_ = Model::LoadFromOBJ("TestBox");
//		decltype(models)::iterator it = models.find(objectData.fileName);
//		if (it != models.end()) { model_ = it->second; }
//
//		// ���f�����w�肵��3D�I�u�W�F�N�g�𐶐�
//		Object3d* mapObject = Object3d::Create();
//		mapObject->SetModel(model_);
//		// ���W
//		DirectX::XMFLOAT3 scale;
//		DirectX::XMStoreFloat3(&scale, objectData.scaling);
//		mapObject->SetSize(scale);
//
//		// ��]�p
//		DirectX::XMFLOAT3 rot;
//		DirectX::XMStoreFloat3(&rot, objectData.rotation);
//		mapObject->SetRotation(rot);
//
//		// ���W
//		DirectX::XMFLOAT3 pos;
//		DirectX::XMStoreFloat3(&pos, objectData.position);
//		mapObject->SetPosition(pos);
//
//		//�R���C�_�[
//		DirectX::XMFLOAT3 center;
//		DirectX::XMFLOAT2 radius;
//		DirectX::XMStoreFloat3(&center, objectData.center);
//		DirectX::XMStoreFloat2(&radius, objectData.size);
//
//		mapObject->SetCollider(new BoxCollider({ center.x,center.y+radius.y/2,center.z }, { radius.x/2,radius.y/2 }));
//		// �z��ɓo�^
//		objects.push_back(mapObject);
//	}
//}
