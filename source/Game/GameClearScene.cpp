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
	spriteCommon->Loadtexture(1, "white1x1.png");
	//��x�����錾���Ȃ�
	Object3d::StaticInitialize(directXCom->GetDevice(), camera);
}

void GameClearScene::Finalize()
{
}

void GameClearScene::Update()
{
}

void GameClearScene::Draw()
{
}
