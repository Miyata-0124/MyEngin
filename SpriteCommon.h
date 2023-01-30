#include "DirectXCommon.h"
#include <DirectXMath.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#include <string>

using namespace DirectX;

XMFLOAT3 vertices[] = {
			{-0.5f,-0.5f,0.0f}, //左下
			{-0.5f,+0.5f,0.0f}, //左上
			{+0.5f,-0.5f,0.0f}, //右下
};

class SpriteCommon
{
private:
	//定数バッファ用データ構造体(マテリアル)
	struct ConstBufferDataMaterial {
		XMFLOAT4 color;//色(RGBA)
	};

	//定数バッファ用データ構造体
	struct ConstBufferDataTransform {
		XMMATRIX mat;//3D変換行列
	};

public:
	void Initialize(DirectXCommon* dxCommon_);
	void Update();
	HRESULT GetResult() { return result; }
private:
	DirectXCommon *dxCommon;
	HRESULT	result;
	ID3D12Resource* vertBuff = nullptr;
	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	// グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	// パイプランステートの生成
	ID3D12PipelineState* pipelineState = nullptr;
	// ルートパラメータの設定
	D3D12_ROOT_PARAMETER rootParam[3] = {};
	// ルートシグネチャ
	ID3D12RootSignature* rootSignature;
	// ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	//ヒープ設定
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	//定数バッファ
	ID3D12Resource* constBuffMaterial = nullptr;
	ID3D12Resource* constBuffTransform0 = nullptr;
	ConstBufferDataTransform* constMapTransform0 = nullptr;
	// 頂点バッファの設定
	D3D12_HEAP_PROPERTIES heapProp{}; // ヒープ設定

	ID3DBlob* rootSigBlob = nullptr;

	ID3DBlob* vsBlob = nullptr; // 頂点シェーダオブジェクト
	ID3DBlob* psBlob = nullptr; // ピクセルシェーダオブジェクト
	ID3DBlob* errorBlob = nullptr; // エラーオブジェクト
};
