#include "header/Game/OverSprite.h"

void OverSprite::Initialize(SpriteCommon* spriteCommon)
{
	overSprite = new Sprite();
	overSprite->Initialize(spriteCommon, 1);
	overSprite->SetAnchorPoint(XMFLOAT2(0, 0));
	overSprite->SetSize(XMFLOAT2(WinApp::window_width, WinApp::window_height));
	overSprite->SetPosition({ 0,0 });
}

void OverSprite::Update()
{
	//動かすために座標を取得
	XMFLOAT2 position = overSprite->GetPosition();
	if (!isBlackOut)
	{

	}
}

void OverSprite::Draw()
{
}

void OverSprite::Reset()
{
}
