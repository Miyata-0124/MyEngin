#include "header/Game/BlackOut.h"
#include "easing/Easing.h"

void BlackOut::Initialize(SpriteCommon* spriteCommon)
{
	blackOut = new Sprite();
	blackOut ->Initialize(spriteCommon, 2);
	blackOut ->SetAnchorPoint(XMFLOAT2(0, 0));
	blackOut ->SetSize(XMFLOAT2(WinApp::window_width, WinApp::window_height));
	blackOut ->SetPosition({ 0,0 });
	blackOut ->SetColor({ 0,0,0,0 });
}

void BlackOut::Update(int sceneNum_, bool isBlackOut_)
{
	sceneNum = sceneNum_;
	isBlackOut = isBlackOut_;

	if (sceneNum == 0)//タイトル
	{
		//暗転させるのか判断
		if (isBlackOut)
		{
			//フェードイン追加
			if (minalpha < maxalpha)
			{
				minalpha += 0.01f;
			}
			blackOut->SetColor({ 0, 0, 0, minalpha });
			if (minalpha > maxalpha)
			{
				min = 0.0f;
				sceneNum = 1;
			}

		}
	}
	
	//開始演出
	if (sceneNum == 1)//ゲーム内
	{
		if (isBlackOut)
		{
			if (blink == slowOpen)
			{
				minalpha -= 0.01f;
				if (minalpha <= 0.6f)
				{
					blink = slowClose;
					blinkCount += 1;
				}
			}
			else if (blink == slowClose)
			{
				minalpha += 0.01f;
				if (minalpha >= 0.9f)
				{
					if (blinkCount < 3)
					{
						blink = slowOpen;
					}
					else
					{
						blink = Open;
					}
					blinkCount += 1;
				}
			}
			else if (blink == Open)
			{
				minalpha -= 0.02f;
			}

			blackOut->SetColor({ 0, 0, 0, minalpha });
			if (minalpha <= 0.0f)
			{
				minalpha = 0.0f;
				isBlackOut = false;
			}

		}
		blackOut->Update();
	}
}

void BlackOut::Draw()
{
	blackOut->SetIsInvisible(false);
	blackOut->SetTexIndex(2);
	blackOut->Draw();
}