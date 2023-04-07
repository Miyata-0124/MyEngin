#pragma region before includer

//#include<string>
//#include <DirectXMath.h>
//#include<d3dcompiler.h>
//#include"DirectXTex/DirectXTex.h"
//#include<cassert>
//#include<vector>
//
//#pragma	comment(lib,"d3dcompiler.lib")
//#pragma	comment(lib, "d3d12.lib")
//#pragma	comment(lib,"dxgi.lib")
#pragma endregion
//����N���X
#include"Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include"SpriteCommon.h"
#include"Sprite.h"
#include"Object3d.h"
#include"Model.h"

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
	spriteCommon->Loadtexture(1, "reimu.png");
	spriteCommon->Loadtexture(2, "test.png");
#pragma	region	�ŏ��̃V�[���̏�����
	//��x�����錾���Ȃ�
	Object3d::StaticInitialize(directXCom->GetDevice(), WinApp::window_width, WinApp::window_height);
	//�X�v���C�g
	Sprite* sprite = new Sprite();
	sprite->Initialize(spriteCommon, 1);
	sprite->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	sprite->SetSize(XMFLOAT2(100.0f, 100.0f));
	sprite->SetPosition({ 150,50 });

	Sprite* sprite2 = new Sprite();
	sprite2->Initialize(spriteCommon, 2);
	sprite2->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	sprite2->SetSize(XMFLOAT2(100.0f, 100.0f));
	sprite2->SetPosition({ 50,50 });
	//���f��
	Model* model = Model::LoadFromOBJ("sphere");
	Model* model2 = Model::LoadFromOBJ("wall");
	//3d�I�u�W�F�N�g����
	Object3d* obj3d = Object3d::Create();
	Object3d* obj3d2 = Object3d::Create();
	//model�N���X���Ђ��t��
	obj3d->SetModel(model);
	obj3d->SetSize({ 5,5,5 });
	obj3d->SetPosition({ -5,0,0 });

	obj3d2->SetModel(model2);
	obj3d2->SetSize({ 5,5,5 });
	obj3d2->SetPosition({ 5,0,0 });
	//�ϐ�
#pragma	endregion
	while (true)
	{

#pragma region ���b�Z�[�W
		if (winApp->ProcessMessage()) {
			break;
		}
#pragma endregion

#pragma region ���t���[������

		input->Update();

		//������0�L�[��������Ă���
		if (input->TriggerKey(DIK_0))
		{
			OutputDebugStringA("Hit 0\n");//�o�̓E�B���h�E�ɕ\��
		}
#pragma region �X�v���C�g�ړ�
		{
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
		}
#pragma endregion
		obj3d->Update();
		obj3d2->Update();
		//-------------------�`�揈��-------------------
		//Direct���t���[�������@��������
		directXCom->PreDraw();
		Object3d::PreDraw(directXCom->GetCommandList());
		obj3d->Draw();
		obj3d2->Draw();
		Object3d::PostDraw();

		//sprite->SetIsInvisible(true);
		sprite->SetTexIndex(1);
		sprite->Draw();
		sprite2->SetTexIndex(2);
		sprite2->Draw();
		//
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
	delete model;
	delete model2;
	delete obj3d;
#pragma	endregion
	return 0;
}