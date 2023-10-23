#include "header/Game/TitleSprite.h"
#include "easing/Easing.h"

void TitleSprite::Initialize(SpriteCommon* spriteCommon)
{
	sprite = new Sprite();
	sprite->Initialize(spriteCommon, 1);
	sprite->SetAnchorPoint(XMFLOAT2(0, 0));
	sprite->SetSize(XMFLOAT2(WinApp::window_width, WinApp::window_height));
	sprite->SetPosition({ 0,0 });
}

void TitleSprite::Update(Input* input, int sceneNum_, bool isBlackOut_)
{
	sceneNum = sceneNum_;
	isBlackOut = isBlackOut_;
	if (sceneNum == 0)
	{
		//“®‚©‚·‚½‚ß‚ÉÀ•W‚ðŽæ“¾
		XMFLOAT2 position = sprite->GetPosition();
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

		//Ø‚è‘Ö‚¦
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
		sprite->SetPosition(position);
	}
}

void TitleSprite::Draw()
{
	sprite->SetIsInvisible(false);
	sprite->SetTexIndex(1);
	sprite->Draw();
}
