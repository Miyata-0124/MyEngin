#include "GameScene.h"


/// <summary>
/// ����������
/// </summary>
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
	spriteCommon->Loadtexture(2, "testpar1.png");

#pragma	region	�V�[���̏�����
//ViewProjection
//	std::unique_ptr<ViewProjection>camera = std::make_unique<ViewProjection>();
//	camera->Initialeze();
//	//��x�����錾���Ȃ�
	Object3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	FbxObject3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);

	//�X�v���C�g
	sprite->Initialize(spriteCommon, 1);
	sprite->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	sprite->SetSize(XMFLOAT2(320.0f, 180.0f));
	sprite->SetPosition({ 160,90 });
	//�|�X�g�G�t�F�N�g�p�e�N�X�`���ǂݍ���
	/*postEffect->Initialize(spriteCommon, 2);
	postEffect->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	postEffect->SetSize(XMFLOAT2(320.0f, 180.0f));
	postEffect->SetPosition({ 480,90 });*/

	//jsonLoader->LoadFlomJSONInternal(".json")

	model = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

	jsonLoader = JsonLoader::LoadFlomJSONInternal("test");

	object1->initialize();
	object1->SetModel(model);
	object1->SetRotation({ 0,60,0 });
	object1->SetPosition({ 0,-3,0 });
	object1->PlayAnimation();
	//
	//	Sprite* sprite2 = new Sprite();
	//	sprite2->Initialize(spriteCommon, 2);
	//	sprite2->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	//	sprite2->SetSize(XMFLOAT2(100.0f, 100.0f));
	//	sprite2->SetPosition({ 50,50 });
	//	//���f��
	//	Model* model1 = Model::LoadFromOBJ("sphere");
	//	Model* model2 = Model::LoadFromOBJ("wall");
		//3d�I�u�W�F�N�g����
	//	Object3d* obj3d = Object3d::Create();
	//	Object3d* obj3d2 = Object3d::Create();
	//
		//model�N���X���Ђ��t��
	//	obj3d->SetModel(model1);
	//	obj3d->SetSize({ 2,2,2 });
	//	obj3d->SetPosition({ 15,0,0 });
	//
	//	obj3d2->SetModel(model2);
	//	obj3d2->SetSize({ 2,2,2 });
	//	obj3d2->SetPosition({ 15,0,0 });
	//#pragma region �p�[�e�B�N���֌W
	//	//�p�[�e�B�N��
	//	Particle::StaticInitialize(directXCom->GetDevice(), camera.get());
	//	Particle::LoadTexture(1, "MK.png");
	//	Particle::LoadTexture(2, "testpar1.png");
	//	Particle* particle = nullptr;
	//	// �����̐����̓e�N�X�`���ǂݍ��݂̃C���f�b�N�X�i���o�[
	//	particle = Particle::Create(1);
	//	particle->Update();
	//#pragma	endregion

	for (auto& objectData : jsonLoader->objects) {
		Model* model = nullptr;
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end()) {
			model = it->second;
		}

		// ���f�����w�肵��3D�I�u�W�F�N�g�𐶐�
		Object3d* newObject = Object3d::Create();
		newObject->SetModel(model);


		// ���W
		DirectX::XMFLOAT3 pos;
		DirectX::XMStoreFloat3(&pos, objectData.position);
		newObject->SetPosition(pos);

		// ��]�p
		DirectX::XMFLOAT3 rot;
		DirectX::XMStoreFloat3(&rot, objectData.rotation);
		newObject->SetRotation(rot);

		// ���W
		DirectX::XMFLOAT3 scale;
		DirectX::XMStoreFloat3(&scale, objectData.scaling);
		newObject->SetSize(scale);

		// �z��ɓo�^
		objects.push_back(newObject);
	}
}


/// <summary>
/// �X�V����
/// </summary>
void GameScene::Update()
{
	///���ꂼ��̃N���X��Update�̂݋L�q
	//�L�[���
	input->Update();

	//{
	//	XMFLOAT3 eye = camera->GetEye();
	//	XMFLOAT3 traget = camera->GetTarget();
	//	//eye.z -= 0.1f;

	//	camera->SetEye(eye);
	//	camera->Update();
	//}
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
		//obj3d->Update();
		/*obj3d2->Update();
		particle->Update();*/

	object1->Update();
	for (auto object : objects) {
		object->Update();
	}
}


/// <summary>
/// �`�揈��
/// </summary>
void GameScene::Draw()
{
	//�`�揈���������火
	directXCom->PreDraw();
	//�w�i


	//�I�u�W�F�N�g
	//object1->Draw(directXCom->GetCommandList());
	//Object3d::PreDraw(directXCom->GetCommandList());
	//obj3d->Draw();
	//obj3d2->Draw();

	//Object3d::PostDraw();
	//Particle::PreDraw(directXCom->GetCommandList());
	//particle->Draw();
	//Particle::PostDraw();

	// UI�֘A
	//sprite->SetIsInvisible(false);
	//sprite->SetTexIndex(1);
	//sprite->Draw();

	/*postEffect->SetIsInvisible(false);
	postEffect->SetTexIndex(2);
	postEffect->Draw();*/
	/*sprite2->SetTexIndex(2);
	sprite2->Draw();*/
	for (auto object : objects) {
		object->Draw();
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
	delete postEffect;
	//delete model;
	delete object1;
	//delete model1;
	//delete model2;
	//delete obj3d;
}
