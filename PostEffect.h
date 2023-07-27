#pragma once
#include "Sprite.h"
class PostEffect : 
	public Sprite
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(SpriteCommon* spriteCommon_, uint32_t texIndex);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="comList">�R�}���h���X�g</param>
	void Draw(ID3D12GraphicsCommandList* comList);

	//�`��p�e�N�X�`���R�}���h
	void SetTextureCommands(uint32_t index);
	//�e�N�X�`���ԍ�
	void SetTexIndex(const uint32_t texIndex_) { texIndex = texIndex_; }
private:
	SpriteCommon* spriteCommon;
	DirectXCommon* directXCom;

	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
	ID3D12DescriptorHeap* descHeapSRV;
	ID3D12PipelineState* pipelineState = nullptr;
	UINT incrementSize;
	ID3D12RootSignature* rootSignature;
	//�[�x�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	//�����_�[�^�[�Q�b�g1
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	//�f�v�X�X�e���V���r���[
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapDSV;
	//�e�N�X�`���̔ԍ�
	uint32_t texIndex = 0;
};

