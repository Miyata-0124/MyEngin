#include "PostEffect.h"
#include "WinApp.h"
#include <d3dx12.h>

using namespace DirectX;

//�C���f�b�N�X�f�[�^
unsigned short postIndices[] = {
	0,1,2,
	1,2,3,
};

void PostEffect::Initialize(SpriteCommon* spriteCommon,uint32_t texIndex)
{
	HRESULT result;
	Sprite::Initialize(spriteCommon, texIndex);

	//�e�N�X�`�����\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		WinApp::window_height,
		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);

	result = directXCom->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK,
			D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		nullptr,
		IID_PPV_ARGS(&texBuff));
	assert(SUCCEEDED(result));

	{//�e�N�X�`����ԃN���A
		//��f��
		const UINT pixelCount = WinApp::window_width + WinApp::window_height;
		//�摜
		const UINT rowPitch = sizeof(UINT) * WinApp::window_width;
		//�摜�S�̂̃T�C�Y
		const UINT depthPitch = rowPitch * WinApp::window_height;
		//�C���[�W
		UINT* img = new UINT[pixelCount];
		for (int i = 0; i < pixelCount; i++) { img[i] = 0xff0000ff; }

		//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
		result = texBuff->WriteToSubresource(0, nullptr, img, rowPitch, depthPitch);
		assert(SUCCEEDED(result));
		delete[] img;
		//����p14����
	}
}

void PostEffect::Draw(ID3D12GraphicsCommandList* comList)
{
	//srvHeap = spriteCommon->GetSrvHeap();
	comList = directXCom->GetCommandList();
	matWorld = XMMatrixIdentity();
	//matWorld.r[0].m128_f32[0] = 2.0f / directXCom->GetSwapChainDesc().Width;
	//matWorld.r[1].m128_f32[1] = -2.0f / directXCom->GetSwapChainDesc().Height;
	//matWorld *= XMMatrixScaling(1.0f, 1.0f, 0.0f);
	matWorld *= XMMatrixRotationZ(XMConvertToRadians(rotation));
	matWorld *= XMMatrixTranslation(position.x, position.y, 0.0f);

	constMap->color = color;
	constMap->mat = matWorld * matProjection;

	//��\��
	if (isInvisible)
	{
		return;
	}

	spriteCommon->SetTextureCommands(texIndex);

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	comList->IASetVertexBuffers(0, 1, &vbView);
	//�萔�o�b�t�@�r���[�iCBV�j�̐ݒ�R�}���h
	comList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());

	//�C���f�B�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	comList->IASetIndexBuffer(&ibView);
	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	//comList->SetGraphicsRootConstantBufferView(2, constBuff->GetGPUVirtualAddress());
	// �`��R�}���h
	comList->DrawIndexedInstanced(_countof(postIndices), texIndex, 0, 0, 0);//�S�Ă̒��_���g���ĕ`��
}
