#include "GameScene.h"
//#include "Affine.h"

void GameScene::Initialize() {
	//�R���\�[���ւ̕����o��
	/*�R���\�[���E�E�E�L�`�Ńp�\�R���S�ʂ̓��́E�o�͗p�̑��u�̂��Ƃ��w���A��ɃL�[�{�[�h��f�B�X�v���C�̂���*/
	//OutputDebugStringA("Hello,DirectX!!\n");

	//WindowsAPI�̏�����
	winApp = new WinApp();
	winApp->Initialize();

	//DirectX���������� ��������
	/*DirectX�E�E�E�}�C�N���\�t�g���J�������Q�[���E�}���`���f�B�A�����p��API�̏W��*/
	/*API�E�E�EApplication Programming Interface�̗�
	�\�t�g�E�F�A����OS�̋@�\�𗘗p���邽�߂̎d�l�܂��̓C���^�[�t�F�[�X(���҂̊Ԃŏ���M���Ȃǂ����Ƃ肷�邽�߂̎菇��K����߂�����)�̑���
	�A�v���P�[�V�����̊J����e�Ղɂ��邽�߂̃\�t�g�E�F�A�����̂��Ƃ�����*/
	//HRESULT result;

	//DirectX�̏�����
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//���͂̏�����
	input = new Input();
	input->Initialize(winApp);

	//3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	//�`�揉������������

	//�J�����̏�����
	Object3d::SetEye({ 15.0f,20.0f,-20.0f });
	Object3d::SetTarget({ 0, 0, 0 });

	//�X�v���C�g���ʕ��̏�����
	spriteCommon = new SpriteCommon();
	spriteCommon->Initialize(dxCommon);

	//�e�N�X�`���ǂݍ���
	spriteCommon->LoadTexture(1, "reimu.png");
	spriteCommon->LoadTexture(0, "test.png");

	sprite->Initialize(spriteCommon);
	sprite1->Initialize(spriteCommon);

	stageObject = Object3d::Create();
	//object3d2 = Object3d::Create();
	model = Model::LoadFromOBJ("wall");
	//model2 = Model::LoadFromOBJ("triangle_mat");
	//�I�u�W�F�N�g�Ƀ��f�����Ђ��Â���
	stageObject->SetModel(model);
	//object3d2->SetModel(model2);

	stageObject->SetScale({ 10.0f,10.0f,10.0f });

	//viewProjection_.eye  { 0.0f,0.0f,-50.0f };
	//viewProjection_.UpdateView();
	//Affine::CreateAffine(worldTransform_);
	stageObject->Update();

	//worldTransform_.UpdateMatWorld();
	//worldTransform_.Initialize();
	//worldTransform_.scale_ = { 7.0f,7.0f,7.0f };
	//worldTransform_.translation_ = { 0.0f,0.0f,0.0f };
	//Affine::CreateAffine(worldTransform_);

	//worldTransform_.UpdateMatWorld();
}

void GameScene::Finalize() {
	//WindowsAPI�̏I������
	winApp->Finalize();

	//�X�v���C�g���
	delete sprite;
	delete sprite1;
	delete spriteCommon;
	//3D�I�u�W�F�N�g���
	delete stageObject;
	//delete object3d2;
	//3D���f�����
	delete model;
	delete model2;
	//DirectX���
	delete dxCommon;
	//���͉��
	delete input;
	//WindowsAPI���
	delete winApp;

}

void GameScene::Update() {


	//DirectX���t���[������ ��������

	//���͂̍X�V
	input->Update();
	sprite->Update(spriteCommon);
}

void GameScene::Draw() {
	//�`��O����
	dxCommon->PreDraw();

	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());

	//3D�I�u�W�F�N�g�̕`��
	stageObject->Draw();
	//object3d2->Draw();
	//3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	//�X�v���C�g�`��O����
	spriteCommon->PreDraw();

	////�`��R�}���h��������
	spriteCommon->Update(dxCommon);
	//sprite->SetPosition(position);
	sprite1->SetPosition({ 100.0f,100.0f });
	sprite->SetIndex(0);
	sprite1->SetIndex(1);
	//sprite1->SetTextureSize({ 500.0f,450.0f });

	//sprite->Draw(spriteCommon);
	//sprite1->Draw(spriteCommon);
	////�`��R�}���h�����܂�

	//�X�v���C�g�`��㏈��
	spriteCommon->PostDraw();


	dxCommon->PostDraw();


	//DirectX���t���[������ �����܂�
}