#include "header/Game/TitleSprite.h"
#include "easing/Easing.h"

void TitleSprite::Initialize(SpriteCommon* spriteCommon)
{
	titleSprite = new Sprite();
	titleSprite->Initialize(spriteCommon, 1);
	titleSprite->SetAnchorPoint(XMFLOAT2(0, 0));
	titleSprite->SetSize(XMFLOAT2(WinApp::window_width, WinApp::window_height));
	titleSprite->SetPosition({ 0,0 });
}

void TitleSprite::Update(Input* input, int sceneNum_, bool isBlackOut_)
{
	sceneNum = sceneNum_;
	isBlackOut = isBlackOut_;
	if (sceneNum == 0)
	{
		//���������߂ɍ��W���擾
		XMFLOAT2 position = titleSprite->GetPosition();
		if (!UIFlag) {
			if (position.x < 15)
			{
				UIspeed.x = 0.4f;
			}
			else
			{
				UIFlag = true;
			}
		}
		else
		{
			if (position.x > -15)
			{
				UIspeed.x = -0.4f;
			}
			else
			{
				UIFlag = false;
			}
		}
		position.x += UIspeed.x;
		position.y += UIspeed.y;

		//�؂�ւ�
		if (input->TriggerKey(DIK_SPACE) && ChengeScene == false)
		{
			startY = position.y;
			endY = startY + 720;
			ChengeScene = true;
		}
		if (ChengeScene)
		{
			if (min <= max)
			{
				min += 0.03f;
			}
			y = min / max;
			position.y = startY + (endY - startY) * Easing::easeInSine(y);


			if (min > max)
			{
				blackOutTimer--;
				if (blackOutTimer <= 0.0f)
				{
					blackOutTimer = 300.0f;
					ChengeScene = false;
					isBlackOut = true;
				}
			}
		}
		titleSprite->SetPosition(position);
	}
}

void TitleSprite::Draw()
{
	titleSprite->SetIsInvisible(false);
	titleSprite->SetTexIndex(1);
	titleSprite->Draw();
}

void TitleSprite::Reset()
{
	titleSprite->SetAnchorPoint(XMFLOAT2(0, 0));
	titleSprite->SetSize(XMFLOAT2(WinApp::window_width, WinApp::window_height));
	titleSprite->SetPosition({ 0,0 });

	//�^�C�g���Ȃǂ�UI���
	ChengeScene = false;
	//UI�֘A
	UIFlag = false;
	UIspeed = { 0,0 };

	sceneNum = 0;
	//�g�k�t���O
	//�Ó]
	min = 0.0f;
	max = 1.0f;
	startY = 0.0f;
	endY = 720.0f;
	y = min / max;
	isBlackOut = false;
	blackOutTimer = 300.0f;
	minalpha = 0.0f;
	maxalpha = 1.0f;
}
