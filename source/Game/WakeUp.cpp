#include "header/Game/WakeUp.h"

void WakeUp::Initialize(SpriteCommon* spriteCommon)
{
	wakeUp = new Sprite();
	wakeUp->Initialize(spriteCommon, 1);
	wakeUp->SetAnchorPoint(XMFLOAT2(0, 0));
	wakeUp->SetSize(XMFLOAT2(WinApp::window_width, WinApp::window_height));
	wakeUp->SetPosition({ 0,0 });
	wakeUp->SetColor({ 0,0,0,0 });

	blink = Blink::slowOpen;
	blinkCount = 0;
}

void WakeUp::Update()
{
	//äJénââèo
	if (blink == slowOpen)
	{
		minAlpha -= 0.01f;
		if (minAlpha <= 0.6f)
		{
			blink = slowClose;
			blinkCount += 1;
		}
	}
	else if (blink == slowClose)
	{
		if (blinkCount >= 3)
		{
			minAlpha += 0.03f;
		}
		else
		{
			minAlpha += 0.01f;
		}
				
		if (minAlpha >= 0.9f)
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
		minAlpha -= 0.02f;
	}

	wakeUp->SetColor({ 0, 0, 0, minAlpha });
	if (minAlpha <= 0.0f)
	{
		minAlpha = 0.0f;
		blinkCount = 0;
	}
	wakeUp->Update();
}

void WakeUp::Draw()
{
	wakeUp->SetIsInvisible(false);
	wakeUp->SetTexIndex(1);
	wakeUp->Draw();
}

void WakeUp::Reset()
{
}
