#pragma once //�X�v���C�g1����
#include "SpriteCommon.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
using namespace DirectX;

class Sprite
{
public: // �����o�֐�
	// ������
	void Initialize(SpriteCommon* spriteCommon_);
	void Draw();
private:
	SpriteCommon* spriteCommon;
	DirectXCommon* dxCommon;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>CommandList;
	HRESULT result;
	//���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
};

