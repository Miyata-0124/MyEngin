#pragma once
#include "Sprite.h"
class PostEffect : 
	public Sprite
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(SpriteCommon* spriteCommon, uint32_t texIndex);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="comList">�R�}���h���X�g</param>
	void Draw(ID3D12GraphicsCommandList* comList);

	ID3D12Resource* texBuff;
	ID3D12DescriptorHeap* descHeapSRV;
};

