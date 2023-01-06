#pragma once //�X�v���C�g�̋��ʕ���
#include "DirectXCommon.h"
#include <DirectXTex.h>

class SpriteCommon
{
public:
	// ������
	void Initialize(DirectXCommon* dxCommon_);
	DirectXCommon* GetdxCommon()const { return dxCommon; }


	ID3D12PipelineState* GetPipelineState() { return pipelineState; }
	ID3D12RootSignature* GetRootSignature() { return rootSignature; }
private:
	DirectXCommon* dxCommon;
	HRESULT result;
	ID3D12PipelineState* pipelineState = nullptr;
	ID3D12RootSignature* rootSignature;
};
