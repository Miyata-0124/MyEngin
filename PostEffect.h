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

	/// <summary>
	/// �V�[���`��O����
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList);
	/// <summary>
	/// �V�[���`��㏈��
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);
private:
	void CreateHeaps();
private://�\����
	//���_�f�[�^
	struct Vertex {
		XMFLOAT3	pos;//xyz���W
		XMFLOAT2	uv;//uv���W
	};

	//�萔�o�b�t�@�p�f�[�^�i�}�e���A���j
	struct ConstBufferData {
		XMFLOAT4	color;//�F�iRGB�j
		XMMATRIX	mat;//3D�ϊ��s��
	};

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

	//��ʃN���A�J���[
	static const float clearColor[4];
};