#include "header/Game/TutorialUI.h"

void TutorialUI::Initialize(SpriteCommon* spriteCommon)
{
	for (int i = 0; i < 4; i++)
	{
		tutorialUI[i] = new Sprite();
		tutorialUI[i]->Initialize(spriteCommon, i + 6);
		tutorialUI[i]->SetAnchorPoint(XMFLOAT2(0, 0));
		tutorialUI[i]->SetSize(XMFLOAT2(640, 240));
		tutorialUI[i]->SetPosition(XMFLOAT2(0,0));
		tutorialUI[i]->SetIsInvisible(true);
	}
}

void TutorialUI::Update()
{
	if (playerPos <= -45 && playerPos >= -75)
	{
		tutorialUI[0]->SetIsInvisible(false);
		tutorialUI[1]->SetIsInvisible(true);
		tutorialUI[2]->SetIsInvisible(true);
		tutorialUI[3]->SetIsInvisible(true);
	}

	if (playerPos <= 5 && playerPos >= -46)
	{
		tutorialUI[0]->SetIsInvisible(true);
		tutorialUI[1]->SetIsInvisible(false);
		tutorialUI[2]->SetIsInvisible(true);
		tutorialUI[3]->SetIsInvisible(true);
	}

	if (playerPos <= 65 && playerPos >= 6)
	{
		tutorialUI[0]->SetIsInvisible(true);
		tutorialUI[1]->SetIsInvisible(true);
		tutorialUI[2]->SetIsInvisible(false);
		tutorialUI[3]->SetIsInvisible(true);
	}

	if (playerPos <= 145 && playerPos >= 66)
	{
		tutorialUI[0]->SetIsInvisible(true);
		tutorialUI[1]->SetIsInvisible(true);
		tutorialUI[2]->SetIsInvisible(true);
		tutorialUI[3]->SetIsInvisible(false);
	}
}

void TutorialUI::Draw()
{
	for (int i = 0; i < 4; i++)
	{
		tutorialUI[i]->SetTexIndex( i + 6 );
		tutorialUI[i]->Draw();
	}
}

void TutorialUI::Reset()
{
	for (int i = 0; i < 4; i++)
	{
		tutorialUI[i]->SetAnchorPoint(XMFLOAT2(0, 0));
		tutorialUI[i]->SetSize(XMFLOAT2(640, 240));
		tutorialUI[i]->SetPosition({ 10,700 });
	}

}
