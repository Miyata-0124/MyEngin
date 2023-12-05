#include "header/Game/GameTitleScene.h"
#include "header/Game/GameSceneManager.h"
#include "header/Game/Rain.h"
#include "header/Game/GamePlayScene.h"

void GameTitleScene::Initialize(ViewProjection* camera_,Input* input_)
{
	//�L�[���
	input = input_;
	//�X�v���C�g���ʕ����̏�����
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "taitle.png");
	spriteCommon->Loadtexture(2, "white1x1.png");
	//�^�C�g��
	titleSprite->Initialize(spriteCommon);
	blackOut->Initialize(spriteCommon);
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
	//delete rain;
	//�Ó]
	delete blackOut;
}

void GameTitleScene::Update()
{
	#pragma region �p�[�e�B�N��
	rain->Update();
	#pragma endregion

	#pragma region �V�[���؂�ւ����̏���

	titleSprite->Update(input);

	if (titleSprite->GetPosition().y >= landingPoint)
	{
		blackOut->Update();
		if (blackOut->GetMinAlpha() >= blackOut->GetMaxAlpha())
		{
			GameBaseScene* scene = new GamePlayScene();
			sceneManager->SetNextScene(scene);
		}
	}
}

void GameTitleScene::Draw()
{
	//�^�C�g��
	titleSprite->Draw();

	Particle::PreDraw(directXCom->GetCommandList());
	rain->Draw();
	Particle::PostDraw();

	//�Ó]
	blackOut->Draw();
}
