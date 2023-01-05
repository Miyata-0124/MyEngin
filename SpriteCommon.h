#pragma once //�X�v���C�g�̋��ʕ���
#include "DirectXCommon.h"
#include <DirectXTex.h>

class SpriteCommon
{
public:
	// ������
	void Initialize(DirectXCommon* dxCommon_);
	void Draw();
	DirectXCommon* GetdxCommon()const { return dxCommon; }
private:
	DirectXCommon* dxCommon;
	//�p�C�v���C���X�e�[�g�̐���
	ID3D12PipelineState* pipelineState = nullptr;
	//���[�g�V�O�l�`���̐���
	ID3D12RootSignature* rootSignature;
	HRESULT result;
};

