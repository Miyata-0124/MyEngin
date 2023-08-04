#include "GameScene.h"

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
	SpriteCommon::GetInstance()->Initialize(directXCom);
	
}

void GameScene::Update()
{
	///���ꂼ��̃N���X��Update�̂݋L�q
	//�L�[���
	input->Update();
	//�J����
	camera->Update();
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
	//�A�C�e��
	objItem->Update();
	//�n��
	objFloor->Update();
	//�w�i
	objBackGround->Update();
	//obj3d->Update();
	//particle->Update();

	for (auto object : objects) {
		object->Update();
	}

#pragma region �e�N���X�Ԃ̏��󂯓n��
	//�I�u�W�F�N�g
	objItem->SetPPosition(objPlayer->GetPosition());
	objItem->SetRetention(objPlayer->GetRetention());
	objItem->SetDirection(objPlayer->GetDirection());
	//�X�v���C�g


#pragma endregion
	
	//����}�l�[�W���[
	collisionManager->CheckAllCollisions();
}

void GameScene::Draw()
{
	//�`�揈���������火
	directXCom->PreDraw();
	//�w�i


	//�I�u�W�F�N�g
	//object1->Draw(directXCom->GetCommandList());
	Object3d::PreDraw(directXCom->GetCommandList());
	//�v���C���[
	objPlayer->Draw();
	//�A�C�e��
	objItem->Draw();
	//�n��
	//objFloor->Draw();
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

		// ���f�����w�肵��3D�I�u�W�F�N�g�𐶐�
		Object3d* newObject = Object3d::Create();
		newObject->SetModel(model);
		// ���W
		DirectX::XMFLOAT3 scale;
		DirectX::XMStoreFloat3(&scale, objectData.scaling);
		newObject->SetSize(scale);

		// ��]�p
		DirectX::XMFLOAT3 rot;
		DirectX::XMStoreFloat3(&rot, objectData.rotation);
		newObject->SetRotation(rot);

		// ���W
		DirectX::XMFLOAT3 pos;
		DirectX::XMStoreFloat3(&pos, objectData.position);
		newObject->SetPosition(pos);

		////�R���C�_�[
		//DirectX::XMFLOAT3 center;
		// �z��ɓo�^
		objects.push_back(newObject);
	}
}
