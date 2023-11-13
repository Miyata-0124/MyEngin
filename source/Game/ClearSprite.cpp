#include "header/Game/ClearSprite.h"
#include "easing/Easing.h"

void ClearSprite::Initialize(SpriteCommon* spriteCommon)
{
	clearSprite = new Sprite();
	clearSprite->Initialize(spriteCommon, 5);
	clearSprite->SetAnchorPoint(XMFLOAT2(0, 0));
	clearSprite->SetSize(XMFLOAT2(WinApp::window_width, WinApp::window_height));
	clearSprite->SetRotation(0);
	clearSprite->SetPosition({ 0,-720 });
}

void ClearSprite::Update()
{
	//“®‚©‚·‚½‚ß‚ÉÀ•W‚ðŽæ“¾
	XMFLOAT2 position = clearSprite->GetPosition();
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
	}
	else
	{
		if (min <= max)
		{
			min += 0.01f;
		}
		y = min / max;
		position.y = startY + (endY - startY) * Easing::easeOutBounce(y);

	}
	clearSprite->SetPosition(position);
}

void ClearSprite::Draw()
{
	clearSprite->SetIsInvisible(false);
	clearSprite->SetTexIndex(5);
	clearSprite->Draw();
}

void ClearSprite::Reset()
{
	clearSprite->SetSize(XMFLOAT2(WinApp::window_width, WinApp::window_height));
	clearSprite->SetRotation(0);
	clearSprite->SetPosition({ 0,-720 });
	startY = 0.0f;
	min = 0.0f;

	downTimer = 10.0f;

	isBlackOut = false;

	alpha = 0.0f;
}
