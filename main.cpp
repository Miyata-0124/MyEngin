
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <vector>

#include <DirectXTex.h>
#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Sprite.h"
using namespace DirectX;
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#define DIRECTINPUT_VERSION 0x0800 //DirectInput�̃o�[�W�����w��
#include <dinput.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

//Windows�A�v���ł̃G���g���[�|�C���g
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//�R���\�[���ւ̕����o��
	OutputDebugStringA("Hello,Directx!!\n");

	MSG msg{};	//���b�Z�[�W

	//DirectX������������������
#ifdef  _DEBUG
	//�f�o�b�O���C���[���I����
	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
	}
#endif //  _DEBUG
#pragma region ������DirectX

	WinApp* winApp = nullptr;
	// WindowsAPI�̏�����
	winApp = new WinApp();
	winApp->Initialize();

	DirectXCommon* dxCommon = nullptr;
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	Input* input = nullptr;
	input = new Input();
	input->Initialize(winApp);
#pragma endregion
	//DirectX���������������܂�
	//�`�揉��������
	SpriteCommon* spriteCommon = nullptr;
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	Sprite* sprite = nullptr;
	sprite = new Sprite;
	sprite->Initialize(spriteCommon);
	
	
	
	//////�ˉe�ϊ��s��̌v�Z
	//XMMATRIX matProjection =
	//	XMMatrixPerspectiveFovLH(
	//		XMConvertToRadians(45.0f),//�㉺��p45�x
	//		(float)WinApp::window_width / WinApp::window_height,//�A�X�y�N�g��(��ʉ���/��ʏc��)
	//		0.1f, 1000.0f//�O�[,���[
	//	);
	//////�r���[�ϊ��s����v�Z
	//XMMATRIX matview;
	//XMFLOAT3 eye(0, 0, -100);	//�n�_���W
	//XMFLOAT3 target(0, 0, 0);	//�����_���W
	//XMFLOAT3 up(0, 1, 0);		//������x�N�g��
	//matview = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

#pragma region �摜�f�[�^
#pragma region ���\�[�X�f�[�^�쐬
	////�������s�N�Z����
	//const size_t textureWidth = 256;
	////�c�����s�N�Z����
	//const size_t textureHeight = 256;
	////�z��̗v�f��
	//const size_t imageDataCount = textureWidth * textureHeight;
	////�摜�C���[�W�f�[�^
	//XMFLOAT4* imageData = new XMFLOAT4[imageDataCount];//�K�����

	////�S�s�N�Z���̐F��������
	//for (size_t i = 0; i < imageDataCount; i++) {
	//	imageData[i].x = 1.0f; //R
	//	imageData[i].y = 0.0f; //G
	//	imageData[i].z = 0.0f; //B
	//	imageData[i].w = 1.0f; //A
	//}
	////���f�[�^���
	//delete[] imageData;
#pragma endregion
//	TexMetadata metadata{};
//	ScratchImage scratchImg{};
//	//WIC�e�N�X�`���̃��[�h
//	result = LoadFromWICFile(
//		L"Resource/test.png",
//		WIC_FLAGS_NONE,
//		&metadata, scratchImg
//	);
//	ScratchImage mipChain{};
//	//�~�j�}�b�v����
//	result = GenerateMipMaps(
//		scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(),
//		TEX_FILTER_DEFAULT, 0, mipChain);
//	if (SUCCEEDED(result)) {
//		scratchImg = std::move(mipChain);
//		metadata = scratchImg.GetMetadata();
//	}
//	//�ǂݍ��񂾃f�B�q���[�Y�e�N�X�`����SRGB�Ƃ��Ďg��
//	metadata.format = MakeSRGB(metadata.format);
//	//�q�[�v�ݒ�
//	D3D12_HEAP_PROPERTIES textureHeapProp{};
//	textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
//	textureHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
//	textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
//	//���\�[�X�ݒ�
//	D3D12_RESOURCE_DESC textureResourceDesc{};
//	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
//	textureResourceDesc.Format = metadata.format;
//	textureResourceDesc.Width = metadata.width; //��
//	textureResourceDesc.Height = metadata.height; //����
//	textureResourceDesc.DepthOrArraySize = (UINT)metadata.arraySize;
//	textureResourceDesc.MipLevels = (UINT)metadata.mipLevels;
//	textureResourceDesc.SampleDesc.Count = 1;
//
//	//�e�N�X�`���o�b�t�@�̐���
//	ID3D12Resource* texBuff = nullptr;
//	result = dxCommon->GetDevice()->CreateCommittedResource(
//		&textureHeapProp,
//		D3D12_HEAP_FLAG_NONE,
//		&textureResourceDesc,
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&texBuff));
//
//	//�S�~�j�}�b�v�ɂ���
//	for (size_t i = 0; i < metadata.mipLevels; i++) {
//		//�~�j�}�b�v���x�����w�肵�ăC���[�W���擾
//		const Image* img = scratchImg.GetImage(i, 0, 0);
//		//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
//		result = texBuff->WriteToSubresource(
//			(UINT)i,
//			nullptr,				//�S�̈�փR�s�[
//			img->pixels,			//���f�[�^�A�h���X
//			(UINT)img->rowPitch,	//1���C���T�C�Y
//			(UINT)img->slicePitch	//1���T�C�Y
//		);
//		assert(SUCCEEDED(result));
//	}
//
//	//SRV�̍ő��
//	const size_t kMaxSRVCount = 2056;
//
//	//�f�X�N���v�^�q�[�v�̐ݒ�
//	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc{};
//	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
//	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_�[���猩����悤��
//	srvHeapDesc.NumDescriptors = kMaxSRVCount;
//
//	//�ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
//	ID3D12DescriptorHeap* srvHeap = nullptr;
//	result = dxCommon->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvHeap));
//	assert(SUCCEEDED(result));
//
//	//SRV�q�[�v�̐擪�n���h���擾
//	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();
//
//	//�V�F�[�_���\�[�X�r���[
//	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; //�ݒ�\����
//	srvDesc.Format = resDesc.Format; //RGBA float
//	srvDesc.Shader4ComponentMapping =
//		D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
//	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; //2D�e�N�X�`��
//	srvDesc.Texture2D.MipLevels = resDesc.MipLevels;
//
//	//�n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
//	dxCommon->GetDevice()->CreateShaderResourceView(texBuff, &srvDesc, srvHandle);
//
//	//�f�X�N���v�^�����W�̐ݒ�
//	D3D12_DESCRIPTOR_RANGE descriptorRange{};
//	descriptorRange.NumDescriptors = 1; //1�x�ɕ`��Ɏg���e�N�X�`����1���Ȃ̂�1
//	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
//	descriptorRange.BaseShaderRegister = 0; //�e�N�X�`�����W�X�^0��
//	descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
//#pragma endregion
//
//
//	//�l���������ނƎ����ɓ]�������
//	constMapMaterial->color = XMFLOAT4(1, 1, 1, 1);//�F
	
	
	
	
#pragma region �[�x�o�b�t�@
	////���\�[�X�ݒ�
	//D3D12_RESOURCE_DESC depthResourceDesc{};
	//depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	//depthResourceDesc.Width = WinApp::window_width; // �����_�[�^�[�Q�b�g�ɍ��킹��
	//depthResourceDesc.Height = WinApp::window_height; // �����_�[�^�[�Q�b�g�ɍ��킹��
	//depthResourceDesc.DepthOrArraySize = 1;
	//depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT; // �[�x�l�t�H�[�}�b�g
	//depthResourceDesc.SampleDesc.Count = 1;
	//depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL; // �f�v�X�X�e���V��
	////�[�x�l�p�q�[�v�v���p�e�B
	//D3D12_HEAP_PROPERTIES depthHeapProp{};
	//depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	////�[�x�l�̃N���A�ݒ�
	//D3D12_CLEAR_VALUE depthClearValue{};
	//depthClearValue.DepthStencil.Depth = 1.0f; // �[�x�l1.0f(�ő�l)�ŃN���A
	//depthClearValue.Format = DXGI_FORMAT_D32_FLOAT; //�[�x�l�t�H�[�}�b�g
	////���\�[�X����
	//ID3D12Resource* depthBuff = nullptr;
	//result = dxCommon->GetDevice()->CreateCommittedResource(
	//	&depthHeapProp,
	//	D3D12_HEAP_FLAG_NONE,
	//	&depthResourceDesc,
	//	D3D12_RESOURCE_STATE_DEPTH_WRITE, // �[�x�l�������݂Ɏg�p
	//	&depthClearValue,
	//	IID_PPV_ARGS(&depthBuff));
	////�[�x�r���[�p�f�X�N���v�^�q�[�v����
	//D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	//dsvHeapDesc.NumDescriptors = 1; // �[�x�r���[��1��
	//dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // �f�v�X�X�e���V���r���[
	//ID3D12DescriptorHeap* dsvHeap = nullptr;
	//result = dxCommon->GetDevice()->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));
	////�[�x�r���[�쐬
	//D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	//dsvDesc.Format = DXGI_FORMAT_D32_FLOAT; // �[�x�l�t�H�[�}�b�g
	//dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	//dxCommon->GetDevice()->CreateDepthStencilView(
	//	depthBuff,
	//	&dsvDesc,
	//	dsvHeap->GetCPUDescriptorHandleForHeapStart());
	////�f�v�X�X�e���V���X�e�[�g�ݒ�
	//pipelineDesc.DepthStencilState.DepthEnable = true; // �[�x�e�X�g���s��
	//pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // �������݋���
	//pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // ��������΍��i
	//pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT; // �[�x�l�t�H�[�}�b�g

#pragma endregion



#pragma region �u�����h����

	// ���Z����
	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;//���Z(��Ƃ͕�)
	//blenddesc.SrcBlend = D3D12_BLEND_ONE;//�\�[�X�̒l��100%�g��
	//blenddesc.DestBlend = D3D12_BLEND_ONE;//�e�X�g�̒l��100%�g��
	// ���Z����
	//blenddesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;//���Z(��Ƃ͕�)
	//blenddesc.SrcBlend = D3D12_BLEND_ONE;//�\�[�X�̒l��100%�g��
	//blenddesc.DestBlend = D3D12_BLEND_ONE;//�e�X�g�̒l��100%�g��
	// �F���]
	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;//���Z(��Ƃ͕�)
	//blenddesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR;//�\�[�X�̒l��100%�g��
	//blenddesc.DestBlend = D3D12_BLEND_ZERO;//�e�X�g�̒l��100%�g��
	// ����������
	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;//���Z(��Ƃ͕�)
	//blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;//�\�[�X�̒l��100%�g��
	//blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;//�e�X�g�̒l��100%�g��
#pragma endregion
	

	
	
#pragma region �e�N�X�`���T���v���[�̐ݒ�
	//D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	//samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; //���J��Ԃ� (�^�C�����O)
	//samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP; //�c�J��Ԃ� (�^�C�����O)
	//samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP; //���s�J��Ԃ� (�^�C�����O)
	//samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK; //�{�[�_�[�̎��͍�
	//samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR; //�S�Ẵ��j�A���
	//samplerDesc.MaxLOD = D3D12_FLOAT32_MAX; //�~�j�}�b�v�ő�l
	//samplerDesc.MinLOD = 0.0f; //�~�j�}�b�v�ő�l
	//samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	//samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; //�s�N�Z���V�F�[�_����̂ݎg�p�\
#pragma endregion
	
	

	float angle = 0.0f; //�J�����̉�]�p

	//�Q�[�����[�v
	while (true)
	{
		//���b�Z�[�W����
		if (winApp->ProcessMessage()) {
			//�Q�[�����[�v�𔲂���
			break;
		}

		//DirectX���t���[�������@��������
		input->Update();

		//�`��O����
		dxCommon->PreDraw();
		spriteCommon->Update();
		////�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
		//dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetGPUVirtualAddress());

		////SRV�q�[�v�̐ݒ�R�}���h
		//dxCommon->GetCommandList()->SetDescriptorHeaps(1, &srvHeap);
		////SRV�q�[�v�̐擪�n���h�����擾(SRV���w�肵�Ă���͂�)
		//D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();
		////SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
		//dxCommon->GetCommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
		////�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
		//dxCommon->GetCommandList()->IASetIndexBuffer(&ibView);

		//�`��㏈��
		dxCommon->PostDraw();
		//DirectX���t���[�������@�����܂�
	}
	
	winApp->Finalize();
	delete winApp;
	winApp = nullptr;
	delete dxCommon;
	dxCommon = nullptr;
	delete input;
	input = nullptr;
	delete spriteCommon;
	spriteCommon = nullptr;
	delete sprite;
	sprite = nullptr;

	return 0;
}