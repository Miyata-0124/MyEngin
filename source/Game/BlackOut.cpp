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

	if (sceneNum == 0)//�^�C�g��
	{
		//�Ó]������̂����f
		if (isBlackOut)
		{
			//�t�F�[�h�C���ǉ�
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
	
	//�J�n���o
	if (sceneNum == 1)//�Q�[����
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
				if (blinkCount >= 3)
				{
					minalpha += 0.03f;
				}
				else
				{
					minalpha += 0.01f;
				}
				
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
				blinkCount = 0;
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

void BlackOut::Reset()
{
	blackOut->SetColor({ 0,0,0,0 });
	
	blink = slowOpen;

	//�^�C�g���Ȃǂ�UI���
	sceneNum = 0;

	//�g�k�t���O
	//�Ó]
	min = 0.0f;
	max = 1.0f;
	isBlackOut = false;
	minalpha = 0.0f;
	maxalpha = 1.0f;
	blinkCount = 0;
}
