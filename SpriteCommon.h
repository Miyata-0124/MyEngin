#pragma once
#include "DirectXCommon.h"
#include <DirectXTex.h>

//スプライトの共通部分
class SpriteCommon
{
public:
	void Initialize(DirectXCommon* dxCommon);

	ID3D12RootSignature* GetRootSignature() { return rootSignature; }
	ID3D12PipelineState* GetPipelineState() { return pipelineState; }
	DirectXCommon* GetDxCommon() { return dxCommon_; }
private:
	DirectXCommon* dxCommon_;
	HRESULT result;
	//デスクリプタレンジの設定
	D3D12_DESCRIPTOR_RANGE descriptorRange{};
	// グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	//リソース設定
	D3D12_RESOURCE_DESC depthResourceDesc{};
	// ルートシグネチャ
	ID3D12RootSignature* rootSignature;
	// パイプランステートの生成
	ID3D12PipelineState* pipelineState = nullptr;
};

