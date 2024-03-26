#include "header/Game/AP.h"

void AP::Initialize(SpriteCommon* spriteCommon)
{
	for (int i = 0; i < 2; i++)
	{
		ap[i] = new Sprite();
		ap[i]->Initialize(spriteCommon, 4);
		ap[i]->SetAnchorPoint(XMFLOAT2(0, 0));
		ap[i]->SetSize(XMFLOAT2(64, 64));
		ap[i]->SetPosition({ 10 + (64 * (float)i) ,630 });
	}

	apBack = new Sprite();
	apBack->Initialize(spriteCommon, 5);
	apBack->SetAnchorPoint(XMFLOAT2(0, 0));
	apBack->SetSize(XMFLOAT2(128, 64));
	apBack->SetPosition({ 10,630 });
}

void AP::Update()
{
	for (int i = 0; i < 2; i++)
	{
		ap[i]->Update();
	}

	apBack->Update();
}

void AP::Draw()
{
	apBack->SetIsInvisible(false);
	apBack->SetTexIndex(5);
	apBack->Draw();
	for (int i = 0; i < nowAP; i++) 
	{
		ap[i]->SetIsInvisible(false);
		ap[i]->SetTexIndex(4);
		ap[i]->Draw();
	}
	
}

void AP::Reset()
{
	for (int i = 0; i < 2; i++)
	{
		ap[i]->SetAnchorPoint(XMFLOAT2(0, 0));
		ap[i]->SetSize(XMFLOAT2(64, 64));
		ap[i]->SetPosition({10,700});
	}

	apBack->SetAnchorPoint(XMFLOAT2(0, 0));
	apBack->SetSize(XMFLOAT2(128, 64));
	apBack->SetPosition({ 6,700 });
}
