#pragma once
#include "header/Engin/ViewProjection.h"
#include "header/Game/BlackOut.h"
#include "header/Game/TitleSprite.h"

class Rain;

class GameTitleScene
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(ViewProjection* camera_,Input* input_);

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
private:
	Input* input = nullptr;
	//�X�v���C�g�@�\
	SpriteCommon* spriteCommon = SpriteCommon::GetInstance();
	DirectXCommon* directXCom = DirectXCommon::GetInstance();

	//�Q�[�����X�v���C�g
	TitleSprite* titleSprite = new TitleSprite();
	//�Ó]
	BlackOut* blackOut = new BlackOut();
	//�p�[�e�B�N��
	Rain* rain = nullptr;

private:
	//�X�v���C�g�̗����n�_
	float landingPoint = 720;
};

