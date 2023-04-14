//����N���X
#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "ViewProjection.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Particle.h"
#include "Object3d.h"
#include "Model.h"

using namespace DirectX;
using	namespace Microsoft::WRL;

//windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int	WINAPI	WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#pragma	region	��ՃV�X�e���̏�����
#pragma region WindowsAPI�̏�����
	WinApp* winApp = nullptr;
	winApp = new	WinApp;
	winApp->Initialize();
#pragma endregion

#pragma region DirectX����������
	//DirectX�����������@�@��������
	DirectXCommon* directXCom = nullptr;
	directXCom = new DirectXCommon;
	directXCom->Initialize(winApp);

	Input* input = nullptr;
	input = new	Input;
	input->Initialize(winApp);
	//DirectX�����������@�@�����܂�
#pragma endregion
#pragma	endregion
//�X�v���C�g
	SpriteCommon* spriteCommon = nullptr;
	//�X�v���C�g���ʕ����̏�����
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "testpar1.png");
	spriteCommon->Loadtexture(2, "test.png");
#pragma	region	�V�[���̏�����
	//ViewProjection
//	std::unique_ptr<ViewProjection>camera = std::make_unique<ViewProjection>();
//	camera->Initialeze();
//	//��x�����錾���Ȃ�
	Object3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	//�X�v���C�g
	Sprite* sprite = new Sprite();
	sprite->Initialize(spriteCommon, 1);
	sprite->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	sprite->SetSize(XMFLOAT2(1280.0f, 720.0f));
	sprite->SetPosition({ 640,360 });
//
//	Sprite* sprite2 = new Sprite();
//	sprite2->Initialize(spriteCommon, 2);
//	sprite2->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
//	sprite2->SetSize(XMFLOAT2(100.0f, 100.0f));
//	sprite2->SetPosition({ 50,50 });
//	//���f��
//	Model* model = Model::LoadFromOBJ("sphere");
//	Model* model2 = Model::LoadFromOBJ("wall");
//	//3d�I�u�W�F�N�g����
//	Object3d* obj3d = Object3d::Create();
//	Object3d* obj3d2 = Object3d::Create();
//
//	//model�N���X���Ђ��t��
//	obj3d->SetModel(model);
//	obj3d->SetSize({ 2,2,2 });
//	obj3d->SetPosition({ -15,0,0 });
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
#pragma	endregion
	//�X�V����
	while (true)
	{

#pragma region ���b�Z�[�W
		if (winApp->ProcessMessage()) {
			break;
		}
#pragma endregion

#pragma region ���t���[������

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
		/*obj3d->Update();
		obj3d2->Update();
		particle->Update();*/
		//-------------------�`�揈��-------------------
		//Direct���t���[�������@��������
		directXCom->PreDraw();
		/*Object3d::PreDraw(directXCom->GetCommandList());
		obj3d->Draw();
		obj3d2->Draw();

		Object3d::PostDraw();
		Particle::PreDraw(directXCom->GetCommandList());

		particle->Draw();

		Particle::PostDraw();*/

		sprite->SetIsInvisible(false);
		sprite->SetTexIndex(1);
		sprite->Draw();
		/*sprite2->SetTexIndex(2);
		sprite2->Draw();*/
		
		directXCom->PostDraw();

		//Direct���t���[�������@�����܂�
#pragma endregion
		if (input->PushKey(DIK_ESCAPE))
		{
			break;
		}
	}
#pragma	region	�ŏ��̃V�[���̏I��
	winApp->Finalize();
	delete input;
	delete winApp;
	delete directXCom;
	delete spriteCommon;
	delete sprite;
	//delete model;
	//delete model2;
	//delete obj3d;
#pragma	endregion
	return 0;
}