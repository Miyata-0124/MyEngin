#include "Sprite.h"

//���_�f�[�^
XMFLOAT3 vertices[] = {
	{-0.5f,-0.5f,0.0f},
	{-0.5f,+0.5f,0.0f},
	{+0.5f,-0.5f,0.0f},
};

void Sprite::Initialize(SpriteCommon* spriteCommon_)
{
	spriteCommon = spriteCommon_;
	dxCommon = spriteCommon_->GetdxCommon();

	UINT sizeVB = static_cast<UINT>(sizeof(XMFLOAT3) * _countof(vertices));
	D3D12_HEAP_PROPERTIES heapProp{};//�q�[�v�ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]��
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	//���_�o�b�t�@�̐���
	ID3D12Resource* vertBuff = nullptr;
	result = dxCommon->GetResult();
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&heapProp,//�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc,//���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));
	//GPU��̃o�b�t�@�ɓK���������z������(���C����������)�擾
	XMFLOAT3* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	//�S���_�ɑ΂���
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];
	}
	//�q����̉���
	vertBuff->Unmap(0, nullptr);

	//GPU���z�A�h���X
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//���_�o�b�t�@�̃T�C�Y
	vbView.SizeInBytes = sizeVB;
	//���_1���̃f�[�^�T�C�Y
	vbView.StrideInBytes = sizeof(XMFLOAT3);
	
	
}

void Sprite::Draw()
{
	CommandList = dxCommon->GetCommandList();
	//���_�o�b�t�@�r���[�̐ݒ�R�}���h
	CommandList->IASetVertexBuffers(0, 1, &vbView);
	//�v���~�e�B�u�`��̐ݒ�R�}���h
	CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);//�O�p�`���X�g
	//�`��R�}���h
	CommandList->DrawInstanced(_countof(vertices), 1, 0, 0);
}
