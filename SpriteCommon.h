#pragma once //�X�v���C�g�̋��ʕ���
#include "DirectXCommon.h"
#include <DirectXTex.h>

class SpriteCommon
{
public:
	// ������
	void Initialize(DirectXCommon* dxCommon_);
	DirectXCommon* GetdxCommon()const { return dxCommon; }
private:
	DirectXCommon* dxCommon;
	HRESULT result;
};

