#pragma once //�X�v���C�g�̋��ʕ���
#include "DirectXCommon.h"
#include <DirectXTex.h>

class SpriteCommon
{
public:
	// ������
	void Initialize(DirectXCommon* dxCommon_);
	void Draw();
	DirectXCommon* GetdxCommon()const { return dxCommon; }
private:
	DirectXCommon* dxCommon;
	HRESULT result;
	ID3D12PipelineState* pipelineState;
	ID3D12RootSignature* rootSignature;
};

