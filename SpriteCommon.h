#pragma once //スプライトの共通部分
#include "DirectXCommon.h"
#include <DirectXTex.h>

class SpriteCommon
{
public:
	// 初期化
	void Initialize(DirectXCommon* dxCommon_);
	void Draw();
	DirectXCommon* GetdxCommon()const { return dxCommon; }
private:
	DirectXCommon* dxCommon;
	HRESULT result;
	ID3D12PipelineState* pipelineState;
	ID3D12RootSignature* rootSignature;
};

