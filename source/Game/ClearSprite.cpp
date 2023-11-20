#include "header/Game/ClearSprite.h"
#include "easing/Easing.h"

void ClearSprite::Initialize(SpriteCommon* spriteCommon)
{
	clearSprite = new Sprite();
	clearSprite->Initialize(spriteCommon, 1);
	clearSprite->SetAnchorPoint(XMFLOAT2(0, 0));
	clearSprite->SetSize(XMFLOAT2(WinApp::window_width, 120));
	clearSprite->SetRotation(0);
	clearSprite->SetPosition({ 100,-120 });

	startY = clearSprite->GetPosition().y;
	downTimer = 10.0f;
}

void ClearSprite::Update()
{
	//“®‚©‚·‚½‚ß‚ÉÀ•W‚ðŽæ“¾
	XMFLOAT2 position = clearSprite->GetPosition();	
	if (min <= max)
	{
		min += 0.01f;
	}
	y = min / max;
	position.y = startY + (endY - startY) * Easing::easeOutBounce(y);
	

	clearSprite->SetPosition(position);
}

void ClearSprite::Draw()
{
	clearSprite->SetIsInvisible(false);
	clearSprite->SetTexIndex(1);
	clearSprite->Draw();

}

void ClearSprite::Reset()
{
	clearSprite->SetSize(XMFLOAT2(WinApp::window_width, 120));
	clearSprite->SetRotation(0);
	clearSprite->SetPosition({ 0,-120 });
	startY = 0.0f;
	min = 0.0f;

	downTimer = 10.0f;

	alpha = 0.0f;
}

