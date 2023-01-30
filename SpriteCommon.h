#include "DirectXCommon.h"
#include <DirectXMath.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#include <string>

using namespace DirectX;

XMFLOAT3 vertices[] = {
			{-0.5f,-0.5f,0.0f}, //����
			{-0.5f,+0.5f,0.0f}, //����
			{+0.5f,-0.5f,0.0f}, //�E��
};

class SpriteCommon
{
private:
	//�萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
	struct ConstBufferDataMaterial {
		XMFLOAT4 color;//�F(RGBA)
	};

	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataTransform {
		XMMATRIX mat;//3D�ϊ��s��
	};

public:
	void Initialize(DirectXCommon* dxCommon_);
	void Update();
	HRESULT GetResult() { return result; }
private:
	DirectXCommon *dxCommon;
	HRESULT	result;
	ID3D12Resource* vertBuff = nullptr;
	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	// �p�C�v�����X�e�[�g�̐���
	ID3D12PipelineState* pipelineState = nullptr;
	// ���[�g�p�����[�^�̐ݒ�
	D3D12_ROOT_PARAMETER rootParam[3] = {};
	// ���[�g�V�O�l�`��
	ID3D12RootSignature* rootSignature;
	// ���[�g�V�O�l�`���̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	//�萔�o�b�t�@
	ID3D12Resource* constBuffMaterial = nullptr;
	ID3D12Resource* constBuffTransform0 = nullptr;
	ConstBufferDataTransform* constMapTransform0 = nullptr;
	// ���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{}; // �q�[�v�ݒ�

	ID3DBlob* rootSigBlob = nullptr;

	ID3DBlob* vsBlob = nullptr; // ���_�V�F�[�_�I�u�W�F�N�g
	ID3DBlob* psBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ID3DBlob* errorBlob = nullptr; // �G���[�I�u�W�F�N�g
};
