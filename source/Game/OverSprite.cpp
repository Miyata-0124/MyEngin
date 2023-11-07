#include "header/Game/OverSprite.h"
#include "easing/Easing.h"

void OverSprite::Initialize(SpriteCommon* spriteCommon)
{
	overSprite = new Sprite();
	overSprite->Initialize(spriteCommon, 3);
	overSprite->SetAnchorPoint(XMFLOAT2(0, 0));
	overSprite->SetSize(XMFLOAT2(WinApp::window_width, 120));
	overSprite->SetRotation(0);
	overSprite->SetPosition({ 0,-120 });

	blackOut = new Sprite();
	blackOut->Initialize(spriteCommon, 4);
	blackOut->SetAnchorPoint(XMFLOAT2(0, 0));
	blackOut->SetSize(XMFLOAT2(WinApp::window_width, 120));
	blackOut->SetPosition({ 0,600 });
	blackOut->SetColor({ 100,0,0,0 });

	downTimer = 10.0f;
}

void OverSprite::Update()
{
	//“®‚©‚·‚½‚ß‚ÉÀ•W‚ðŽæ“¾
	XMFLOAT2 position = overSprite->GetPosition();
	float rotation = overSprite->GetRotation();
	if (!isBlackOut)
	{
		alpha = 0.0f;
		downTimer -= 0.1f;
		if (downTimer <= 0.0f)
		{
			isBlackOut = true;
			downTimer = 10.0f;
			startY = position.y;
		}
		blackOut->SetColor({ 100, 0, 0, alpha });
	}
	else
	{
		if (min <= max)
		{
			min += 0.01f;
		}
		y = min / max;
		position.y = startY + (endY - startY) * Easing::easeOutBounce(y);

		if (min > max)
		{
			if (!rotDir)
			{
				if (rotSpeed <= 1.0f)
				{
					rotSpeed += 0.1f;
					rotation += rotSpeed;
				}
				else
				{
					if (alpha != 1.0f)
					{
						alpha += 0.01f;
					}
				}

				
			}
		}
		blackOut->SetColor({ 100, 0, 0, alpha });
	}

	overSprite->SetRotation(rotation);
	overSprite->SetPosition(position);
}

void OverSprite::Draw()
{
	overSprite->SetIsInvisible(false);
	overSprite->SetTexIndex(3);
	overSprite->Draw();

	blackOut->SetIsInvisible(false);
	blackOut->SetTexIndex(4);
	blackOut->Draw();
}

void OverSprite::Reset()
{
	overSprite->SetSize(XMFLOAT2(WinApp::window_width, 120));
	overSprite->SetRotation(0);
	overSprite->SetPosition({ 0,-120 });
	startY = 0.0f;
	min = 0.0f;

	blackOut->SetSize(XMFLOAT2(WinApp::window_width, 120));
	blackOut->SetPosition({ 0,600 });

	downTimer = 10.0f;

	isBlackOut = false;

	rotSpeed = 0.0f;

	alpha = 0.0f;
}
