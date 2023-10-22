#include "header/Game/BlackOut.h"
#include "easing/Easing.h"

void BlackOut::Initialize(SpriteCommon* spriteCommon)
{
	sprite = new Sprite();
	sprite ->Initialize(spriteCommon, 2);
	sprite ->SetAnchorPoint(XMFLOAT2(0, 0));
	sprite ->SetSize(XMFLOAT2(WinApp::window_width, WinApp::window_height));
	sprite ->SetPosition({ 0,0 });
	sprite ->SetColor({ 0,0,0,0 });
}

void BlackOut::Update(int sceneNum_, bool isBlackOut_)
{
	sceneNum = sceneNum_;
	isBlackOut = isBlackOut_;

	if (sceneNum == 0)
	{
		//暗転させるのか判断
		if (isBlackOut)
		{
			//フェードイン追加
			if (minalpha < maxalpha)
			{
				minalpha += 0.01f;
			}
			sprite->SetColor({ 0, 0, 0, minalpha });
			if (minalpha > maxalpha)
			{
				min = 0.0f;
				sceneNum = 1;
			}

		}
	}
	
	if (sceneNum == 1)
	{
		if (isBlackOut)
		{
			minalpha -= 0.01f;
			sprite->SetColor({ 0, 0, 0, minalpha });
			if (minalpha <= 0.0f)
			{
				minalpha = 0.0f;
				isBlackOut = false;
			}

		}
		sprite->Update();
	}
}

void BlackOut::Draw()
{
	sprite->SetIsInvisible(false);
	sprite->SetTexIndex(2);
	sprite->Draw();
}