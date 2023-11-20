#include "header/Game/GameClearScene.h"
#include "header/Game/GameSceneManager.h"

#include "header/Game/Player.h"
#include "header/Game/Floor.h"
#include "header/Game/Gate.h"
#include "header/Game/ClearBox.h"

#include "easing/Easing.h"

#include "header/Game/GameTitleScene.h"

void GameClearScene::Initialize(ViewProjection* camera_, Input* input_)
{
	camera = camera_;
	input = input_;

	//�X�v���C�g���ʕ����̏�����
	spriteCommon->Initialize(directXCom);
	spriteCommon->Loadtexture(1, "GameClear.png");
	spriteCommon->Loadtexture(2, "white1x1.png");

	//�N���A
	clearSprite->Initialize(spriteCommon);
	//�Ó]
	blackOut->Initialize(spriteCommon);

	//��x�����錾���Ȃ�
	Object3d::StaticInitialize(directXCom->GetDevice(), camera);

	//�v���C���[���f��
	Model* playerModel = Model::LoadFromOBJ("player");
	//�n�ʉ����f��
	Model* item_ = Model::LoadFromOBJ("Item");
	//��
	Model* gate = Model::LoadFromOBJ("gate");

	Model* clear = Model::LoadFromOBJ("clear");
	//�v���C���[
	objPlayer = Player::Create(playerModel);
	objPlayer->SetInput(input);
	//�n��
	for (int i = 0; i < 3; i++)
	{
		objFloor[i] = Floor::Create(item_);
	}
	objFloor[1]->SetPosition({ 0, 15, 0 });
	objFloor[2]->SetSize({ 1,80,20 });
	objFloor[2]->SetPosition({ 30,0,0 });
	//��
	for (int i = 0; i < 2; i++)
	{
		objGate[i] = Gate::Create(gate);
		objGate[i]->SetGateNum(i);
	}
	objGate[0]->SetPosition({ -25,-40,0 });
	objGate[1]->SetPosition({ -23, 40,0 });

	objClearBox = ClearBox::Create(clear);
}

void GameClearScene::Finalize()
{
	delete blackOut;
	delete clearSprite;
	delete objPlayer;
	delete objClearBox;
	for (int i = 0; i < 3; i++)
	{
		delete objFloor[i];
	}
	for (int i = 0; i < 2; i++)
	{
		delete objGate[i];
	}
}

void GameClearScene::Update()
{
	//�v���C���[
	if (!objClearBox->GetIsGoal())
	{
		objPlayer->Update();
	}
	
	//�n��
	for (int i = 0; i < 3; i++)
	{
		objFloor[i]->Update();
	}
	//��
	for (int i = 0; i < 2; i++)
	{
		objGate[i]->Update();
		if (objGate[i]->GetRotation().x >= 90.0f)
		{
			blackOut->Update();
		}
	}
	if (blackOut->GetMinAlpha() > blackOut->GetMaxAlpha())
	{
		clearSprite->Update();
	}

	if (input->TriggerKey(DIK_R))
	{
		GameBaseScene* scene = new GameTitleScene();
		sceneManager->SetNextScene(scene);
	}

	//����p
	objClearBox->Update();

	//�e�N���X�ɏ���n��
	for (int i = 0; i < 2; i++) {
		objGate[i]->SetIsGoal(objClearBox->GetIsGoal());
	}

	//����}�l�[�W���[
	collisionManager->CheckAllCollisions();
}

void GameClearScene::Draw()
{
	Object3d::PreDraw(directXCom->GetCommandList());
	//�v���C���[
	objPlayer->Draw();
	//�n��
	for (int i = 0; i < 3; i++)
	{
		objFloor[i]->Draw();
	}
	//�S�[���Q�[�g
	for (int i = 0; i < 2; i++)
	{
		objGate[i]->Draw();
	}
	objClearBox->Draw();


	Object3d::PostDraw();

	blackOut->Draw();
	clearSprite->Draw();
}
