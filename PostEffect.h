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
private:
	SpriteCommon* spriteCommon;
	DirectXCommon* directXCom;

	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	ID3D12PipelineState* pipelineState = nullptr;
	UINT incrementSize;
	ID3D12RootSignature* rootSignature;
};

