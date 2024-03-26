#include "header/Game/BlackOut.h"
#include "easing/Easing.h"

void BlackOut::Initialize(SpriteCommon* spriteCommon)
{
	blackOut = new Sprite();
	blackOut ->Initialize(spriteCommon, 1);
	blackOut ->SetAnchorPoint(XMFLOAT2(0, 0));
	blackOut ->SetSize(XMFLOAT2(WinApp::window_width, WinApp::window_height));
	blackOut ->SetPosition({ 0,0 });
	blackOut ->SetColor({ 0,0,0,0 });

	minAlpha = 0.0f;
	maxAlpha = 1.0f;
}

void BlackOut::Update()
{
	//�t�F�[�h�C���ǉ�
	if (minAlpha < maxAlpha)
	{
		minAlpha += 0.01f;
	}

	blackOut->SetColor({ 0, 0, 0, minAlpha });
}

void BlackOut::Draw()
{
	blackOut->SetIsInvisible(false);
	blackOut->SetTexIndex(2);
	blackOut->Draw();
}

void BlackOut::Reset()
{
	blackOut->SetColor({ 0,0,0,0 });

	//�g�k�t���O
	//�Ó]
	minAlpha = 0.0f;
	maxAlpha = 1.0f;
}
