#pragma once //スプライトの共通部分
#include "DirectXCommon.h"
#include <DirectXTex.h>

class SpriteCommon
{
public:
	// 初期化
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
