#pragma once
#include "Sprite.h"
class PostEffect : 
	public Sprite
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(SpriteCommon* spriteCommon_, uint32_t texIndex);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="comList">コマンドリスト</param>
	void Draw(ID3D12GraphicsCommandList* comList);

	//描画用テクスチャコマンド
	void SetTextureCommands(uint32_t index);
	//テクスチャ番号
	void SetTexIndex(const uint32_t texIndex_) { texIndex = texIndex_; }
private:
	SpriteCommon* spriteCommon;
	DirectXCommon* directXCom;

	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	ID3D12DescriptorHeap* descHeapSRV;
	ID3D12PipelineState* pipelineState = nullptr;
	UINT incrementSize;
	ID3D12RootSignature* rootSignature;
	//深度バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	//レンダーターゲット1
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	//デプスステンシルビュー
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapDSV;
	//テクスチャの番号
	uint32_t texIndex = 0;
};

