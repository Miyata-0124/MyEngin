#pragma once
#include "header/2D/Sprite.h"

class BlackOut
{
public:
	void Initialize(SpriteCommon* spriteCommon);
	void Update(int sceneNum_,bool isBlackOut_);
	void Draw();

	int GetScene() { return sceneNum; }
private:
	Sprite* sprite;
private:
	bool UIFlag = false;
	DirectX::XMFLOAT2 UIspeed = { 0,0 };

	//タイトルなどのUI情報
	bool ChengeScene = false;
	int sceneNum = 0;

	//拡縮フラグ
	//暗転
	float min = 0.0f;
	float max = 1.0f;
	float startY = 0.0f;
	float endY = 720.0f;
	float y;
	bool isBlackOut = false;
	float blackOutTimer = 300.0f;
	float minalpha = 0.0f;
	float maxalpha = 1.0f;
};

