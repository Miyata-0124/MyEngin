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

	/// <summary>
	/// シーン描画前処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList);
	/// <summary>
	/// シーン描画後処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);
private:
	void CreateHeaps();
private://構造体
	//頂点データ
	struct Vertex {
		XMFLOAT3	pos;//xyz座標
		XMFLOAT2	uv;//uv座標
	};

	//定数バッファ用データ（マテリアル）
	struct ConstBufferData {
		XMFLOAT4	color;//色（RGB）
		XMMATRIX	mat;//3D変換行列
	};

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

	//画面クリアカラー
	static const float clearColor[4];
};