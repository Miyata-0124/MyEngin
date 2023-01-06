#include "Sprite.h"

//�萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
struct ConstBufferDataMaterial {
	XMFLOAT4 color;//�F(RGBA)
};


// ���_�f�[�^�\����
struct Vertex
{
	XMFLOAT3 pos; //xyz���W
	XMFLOAT3 normal; //�@���x�N�g��
	XMFLOAT2 uv; //uv���W
};
// ���_�f�[�^
Vertex vertices[] = {
	//{	x	  y	   z}	�@�� { u	v }
	// �O
	{{-5.0f,-5.0f,-5.0f},{},{0.0f,1.0f}},//����
	{{-5.0f, 5.0f,-5.0f},{},{0.0f,0.0f}},//����
	{{ 5.0f,-5.0f,-5.0f},{},{1.0f,1.0f}},//�E��
	{{ 5.0f, 5.0f,-5.0f},{},{1.0f,0.0f}},//�E��
	// ��				
	{{-5.0f,-5.0f, 5.0f},{},{0.0f,1.0f}},//����
	{{-5.0f, 5.0f, 5.0f},{},{0.0f,0.0f}},//����
	{{ 5.0f,-5.0f, 5.0f},{},{1.0f,1.0f}},//�E��
	{{ 5.0f, 5.0f, 5.0f},{},{1.0f,0.0f}},//�E��
	// ��				,
	{{-5.0f,-5.0f,  5.0f},{},{0.0f,1.0f}},//����
	{{-5.0f, 5.0f,  5.0f},{},{0.0f,0.0f}},//����
	{{-5.0f,-5.0f, -5.0f},{},{1.0f,1.0f}},//�E��
	{{-5.0f, 5.0f, -5.0f},{},{1.0f,0.0f}},//�E��
	// �E
	{{ 5.0f,-5.0f, -5.0f},{},{0.0f,1.0f}},//����
	{{ 5.0f, 5.0f, -5.0f},{},{0.0f,0.0f}},//����
	{{ 5.0f,-5.0f,  5.0f},{},{1.0f,1.0f}},//�E��
	{{ 5.0f, 5.0f,  5.0f},{},{1.0f,0.0f}},//�E��
	// ��
	{{-5.0f,-5.0f, -5.0f},{},{0.0f,1.0f}},//����
	{{-5.0f,-5.0f,  5.0f},{},{0.0f,0.0f}},//����
	{{ 5.0f,-5.0f, -5.0f},{},{1.0f,1.0f}},//�E��
	{{ 5.0f,-5.0f,  5.0f},{},{1.0f,0.0f}},//�E��
	// ��
	{{-5.0f, 5.0f, -5.0f},{},{0.0f,1.0f}},//����
	{{-5.0f, 5.0f,  5.0f},{},{0.0f,0.0f}},//����
	{{ 5.0f, 5.0f, -5.0f},{},{1.0f,1.0f}},//�E��
	{{ 5.0f, 5.0f,  5.0f},{},{1.0f,0.0f}},//�E��
};
// ���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
UINT sizeVB = static_cast<UINT>(sizeof(vertices[0]) * _countof(vertices));
unsigned short indices[] =
{
	// �O
	0,1,2, //�O�p�`�P
	2,1,3, //�O�p�`�Q
	// ��
	4,6,5, //�O�p�`3
	5,6,7, //�O�p�`4
	// ��
	8,9,10, //�O�p�`5
	10,9,11, //�O�p�`6
	// �E
	12,13,14, //�O�p�`7
	14,13,15, //�O�p�`8
	// ��
	16,18,17, //�O�p�`9
	17,18,19, //�O�p�`10
	// ��
	20,21,22, //�O�p�`11
	22,21,23, //�O�p�`12
};

void Sprite::Initialize(SpriteCommon* spriteCommon_)
{
	spritecommon = spriteCommon_;
	dxCommon = spritecommon->GetDxCommon();
	result = dxCommon->GetResult();
	//�@���̌v�Z
	for (int i = 0; i < _countof(indices) / 3; i++)
	{//�O�p�`1���ƂɌv�Z���Ă���
		//�O�p�`�̃C���f�b�N�X�����o��,�ꎞ�I�ȕϐ��ɓ����
		unsigned short index0 = indices[i * 3 + 0];
		unsigned short index1 = indices[i * 3 + 1];
		unsigned short index2 = indices[i * 3 + 2];
		//�O�p�`���\�����钸�_���W�x�N�g���ɑ��
		XMVECTOR p0 = XMLoadFloat3(&vertices[index0].pos);
		XMVECTOR p1 = XMLoadFloat3(&vertices[index1].pos);
		XMVECTOR p2 = XMLoadFloat3(&vertices[index2].pos);
		//p0->p1�x�N�g��.p0->p2�x�N�g�����v�Z (�x�N�g���v�Z)
		XMVECTOR v1 = XMVectorSubtract(p1, p0);
		XMVECTOR v2 = XMVectorSubtract(p2, p0);
		//�O�ς͗������琂���ȃx�N�g��
		XMVECTOR normal = XMVector3Cross(v1, v2);
		//���K��(������1�ɂ���)
		normal = XMVector3Normalize(normal);
		//���߂��@���𒸓_�f�[�^�ɑ��
		XMStoreFloat3(&vertices[index0].normal, normal);
		XMStoreFloat3(&vertices[index1].normal, normal);
		XMStoreFloat3(&vertices[index2].normal, normal);
	}

	// ���_�o�b�t�@�̐ݒ�
	D3D12_HEAP_PROPERTIES heapProp{}; // �q�[�v�ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB; // ���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	// ���_�o�b�t�@�̐���
	ID3D12Resource* vertBuff = nullptr;

	result = dxCommon->GetDevice()->CreateCommittedResource(
		&heapProp, // �q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc, // ���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));
	assert(SUCCEEDED(result));
	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	Vertex* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	// �S���_�ɑ΂���
	for (int i = 0; i < _countof(vertices); i++) {
		vertMap[i] = vertices[i]; // ���W���R�s�[
	}
	// �q���������
	vertBuff->Unmap(0, nullptr);
	
	// GPU���z�A�h���X
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	// ���_�o�b�t�@�̃T�C�Y
	vbView.SizeInBytes = sizeVB;
	// ���_1���̃f�[�^�T�C�Y
	vbView.StrideInBytes = sizeof(vertices[0]);

	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC cbResourceDesc{};
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferDataMaterial) + 0xff) & ~0xff;//256�o�C�g�A���C�����g
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//�萔�o�b�t�@
	ID3D12Resource* constBuffTransform0 = nullptr;
	ConstBufferDataTransform* constMapTransform0 = nullptr;

	{
		//�q�[�v�ݒ�
		D3D12_HEAP_PROPERTIES cbHeapProp{};
		cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p
		//���\�[�X�ݒ�
		D3D12_RESOURCE_DESC cbResourceDesc{};
		cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		cbResourceDesc.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0xff;//256�o�C�g�A���C�����g
		cbResourceDesc.Height = 1;
		cbResourceDesc.DepthOrArraySize = 1;
		cbResourceDesc.MipLevels = 1;
		cbResourceDesc.SampleDesc.Count = 1;
		cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	}
	//�C���f�b�N�X�f�[�^�S�̂̃T�C�Y
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * _countof(indices));
	//���\�[�X�ݒ�
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB; //�C���f�b�N�X��񂪓��镪�̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//�C���f�b�N�X�o�b�t�@�̐���
	ID3D12Resource* indexBuff = nullptr;
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&heapProp, //�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc, //���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff));

	//�C���f�b�N�X�o�b�t�@���}�b�s���O
	uint16_t* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	//�S�C���f�b�N�X�ɑ΂���
	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i]; //�C���f�b�N�X���R�s�[
	}
	//�}�b�s���O����
	indexBuff->Unmap(0, nullptr);

	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;

	//�萔�o�b�t�@�̐���
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&cbHeapProp,//�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc,//���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffMaterial));
	assert(SUCCEEDED(result));
	//�萔�o�b�t�@�̃}�b�s���O
	ConstBufferDataMaterial* constMapMaterial = nullptr;
	result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial);//�}�b�s���O
	assert(SUCCEEDED(result));

	for (int i = 0; i < _countof(object3ds); i++) {
		//������
		InitializeObject3d(&object3ds[i], dxCommon->GetDevice());

		//�e�q�\���̃T���v��
		if (i > 0) {
			//1�O�̃I�u�W�F�N�g��e�I�u�W�F�N�g�Ƃ���
			object3ds[i].parent = &object3ds[i - 1];
			//�e�I�u�W�F�N�g��9���̑傫��
			object3ds[i].scale = { 0.9f,0.9f,0.9f };
			//�e�I�u�W�F�N�g�ɑ΂���z���܂���30�x��]
			object3ds[i].rotation = { 0.0f,0.0f,XMConvertToRadians(30.0f) };

			//�e�I�u�W�F�N�g�ɑ΂���Z����-8.0���炷
			object3ds[i].position = { 0.0f,0.0f,-8.0f };
		}
	}

	////�ˉe�ϊ��s��̌v�Z
	matProjection =
		XMMatrixPerspectiveFovLH(
			XMConvertToRadians(45.0f),//�㉺��p45�x
			(float)WinApp::window_width / WinApp::window_height,//�A�X�y�N�g��(��ʉ���/��ʏc��)
			0.1f, 1000.0f//�O�[,���[
		);
	////�r���[�ϊ��s����v�Z
	XMFLOAT3 eye(0, 0, -100);	//�n�_���W
	XMFLOAT3 target(0, 0, 0);	//�����_���W
	XMFLOAT3 up(0, 1, 0);		//������x�N�g��
	matview = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

#pragma region �摜�f�[�^
#pragma region ���\�[�X�f�[�^�쐬

#pragma endregion
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	//WIC�e�N�X�`���̃��[�h
	result = LoadFromWICFile(
		L"Resource/test.png",
		WIC_FLAGS_NONE,
		&metadata, scratchImg
	);
	ScratchImage mipChain{};
	//�~�j�}�b�v����
	result = GenerateMipMaps(
		scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(),
		TEX_FILTER_DEFAULT, 0, mipChain);
	if (SUCCEEDED(result)) {
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}
	//�ǂݍ��񂾃f�B�q���[�Y�e�N�X�`����SRGB�Ƃ��Ďg��
	metadata.format = MakeSRGB(metadata.format);
	//�q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	textureHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC textureResourceDesc{};
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc.Format = metadata.format;
	textureResourceDesc.Width = metadata.width; //��
	textureResourceDesc.Height = metadata.height; //����
	textureResourceDesc.DepthOrArraySize = (UINT)metadata.arraySize;
	textureResourceDesc.MipLevels = (UINT)metadata.mipLevels;
	textureResourceDesc.SampleDesc.Count = 1;

	//�e�N�X�`���o�b�t�@�̐���
	ID3D12Resource* texBuff = nullptr;
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&textureHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&textureResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texBuff));

	//�S�~�j�}�b�v�ɂ���
	for (size_t i = 0; i < metadata.mipLevels; i++) {
		//�~�j�}�b�v���x�����w�肵�ăC���[�W���擾
		const Image* img = scratchImg.GetImage(i, 0, 0);
		//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
		result = texBuff->WriteToSubresource(
			(UINT)i,
			nullptr,				//�S�̈�փR�s�[
			img->pixels,			//���f�[�^�A�h���X
			(UINT)img->rowPitch,	//1���C���T�C�Y
			(UINT)img->slicePitch	//1���T�C�Y
		);
		assert(SUCCEEDED(result));
	}

	//SRV�̍ő��
	const size_t kMaxSRVCount = 2056;

	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc{};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_�[���猩����悤��
	srvHeapDesc.NumDescriptors = kMaxSRVCount;

	//�ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�

	result = dxCommon->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvHeap));
	assert(SUCCEEDED(result));

	//SRV�q�[�v�̐擪�n���h���擾
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();

	//�V�F�[�_���\�[�X�r���[
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; //�ݒ�\����
	srvDesc.Format = resDesc.Format; //RGBA float
	srvDesc.Shader4ComponentMapping =
		D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; //2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = resDesc.MipLevels;

	//�n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	dxCommon->GetDevice()->CreateShaderResourceView(texBuff, &srvDesc, srvHandle);


#pragma endregion


	//�l���������ނƎ����ɓ]�������
	constMapMaterial->color = XMFLOAT4(1, 1, 1, 1);//�F
}

void Sprite::Update()
{
	UpdateObject3d(&object3ds[0], matview, matProjection);
}

void Sprite::Draw()
{
	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	dxCommon->GetCommandList()->SetPipelineState(spritecommon->GetPipelineState());
	dxCommon->GetCommandList()->SetGraphicsRootSignature(spritecommon->GetRootSignature());
	// �v���~�e�B�u�`��̐ݒ�R�}���h
	dxCommon->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	dxCommon->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);
	//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetGPUVirtualAddress());

	//SRV�q�[�v�̐ݒ�R�}���h
	dxCommon->GetCommandList()->SetDescriptorHeaps(1, &srvHeap);
	//SRV�q�[�v�̐擪�n���h�����擾(SRV���w�肵�Ă���͂�)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();
	//SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
	dxCommon->GetCommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	dxCommon->GetCommandList()->IASetIndexBuffer(&ibView);
	//�S�I�u�W�F�N�g�ɂ��Ă̏���
	DrawObject3d(&object3ds[0], dxCommon->GetCommandList(), vbView, ibView, _countof(indices));
}
