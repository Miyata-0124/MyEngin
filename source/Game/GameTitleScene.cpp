#include "header/Game/GameTitleScene.h"
#include "header/Game/Rain.h"

void GameTitleScene::Initialize(ViewProjection* camera_,Input* input_)
{
	//�L�[���
	input = input_;
	//�X�v���C�g���ʕ����̏�����
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "taitle.png");
	//�^�C�g��
	titleSprite->Initialize(spriteCommon);
	//��x�����錾����
	Particle::StaticInitialize(directXCom->GetDevice(), camera_);

#pragma region �p�[�e�B�N���֌W
	rain = Rain::Create();
#pragma	endregion
}

void GameTitleScene::Finalize()
{
	//�Q�[�����X�v���C�g
	delete titleSprite;
	//�J
	delete rain;
}

void GameTitleScene::Update()
{
	#pragma region �p�[�e�B�N��
	rain->Update();
	#pragma endregion
	#pragma region �V�[���؂�ւ����̏���

	titleSprite->Update(input, 0);
}

void GameTitleScene::Draw()
{
	//�^�C�g��
	titleSprite->Draw();

	Particle::PreDraw(directXCom->GetCommandList());
	rain->Draw();
	Particle::PostDraw();
}
