#pragma once
#include "Sprite.h"
class PostEffect : 
	public Sprite
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(SpriteCommon* spriteCommon, uint32_t texIndex);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="comList">コマンドリスト</param>
	void Draw(ID3D12GraphicsCommandList* comList);

	ID3D12Resource* texBuff;
	ID3D12DescriptorHeap* descHeapSRV;
};

