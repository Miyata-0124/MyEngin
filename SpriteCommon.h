#pragma once
#include "DirectXCommon.h"
#include <DirectXTex.h>

//�X�v���C�g�̋��ʕ���
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
	//�f�X�N���v�^�����W�̐ݒ�
	D3D12_DESCRIPTOR_RANGE descriptorRange{};
	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC depthResourceDesc{};
	// ���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature;
	// �p�C�v�����X�e�[�g�̐���
	ID3D12PipelineState* pipelineState = nullptr;
};

