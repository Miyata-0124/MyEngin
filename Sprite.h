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

private: // �\����
	struct ConstBufferDataMaterial
	{
		XMFLOAT4 color;
	};

	struct Vertex
	{
		XMFLOAT3 pos; //xyz���W
		XMFLOAT2 uv; // uv���W
	};
	//���_�f�[�^
	Vertex vertices[4] = {
		{{-0.4f,-0.7f,0.0f},{0.0f,1.0f}},// ����
		{{-0.4f,+0.7f,0.0f},{0.0f,0.0f}},// ����
		{{+0.4f,-0.7f,0.0f},{1.0f,1.0f}},// �E��
		{{+0.4f,+0.7f,0.0f},{1.0f,0.0f}},// �E��
	};

private:
	DirectXCommon* dxCommon;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>CommandList;
	HRESULT result;
	//���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{}; 
	ID3D12Resource* constBuffMaterial;
};

