#pragma once
#include "SpriteCommon.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
using namespace DirectX;

//�X�v���C�g�̕���
class Sprite
{
public:
	void Initialize(SpriteCommon* spriteCommon_);
	void Update();
	void Draw();

private: //�\����
	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataTransform {
		XMMATRIX mat;//3D�ϊ��s��
	};

	// 3D�I�u�W�F�N�g�^
	struct Object3d
	{
		//�萔�o�b�t�@
		ID3D12Resource* constBuffTransform;
		//�萔�o�b�t�@�}�b�v
		ConstBufferDataTransform* constMapTransform;
		//�A�t�B���ϊ�
		XMFLOAT3 scale = { 1,1,1 };
		XMFLOAT3 rotation = { 0,0,0 };
		XMFLOAT3 position = { 0,0,0 };
		//���[���h�ϊ��s��
		XMMATRIX matWorld;
		//�e�I�u�W�F�N�g�ւ̃|�C���g
		Object3d* parent = nullptr;
	};

	void InitializeObject3d(Object3d* object, ID3D12Device* device)
	{
		HRESULT result;

		//�萔�o�b�t�@�̃q�[�v�ݒ�
		D3D12_HEAP_PROPERTIES heapProp{};
		heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
		//�萔�o�b�t�@�̃��\�[�X
		D3D12_RESOURCE_DESC resdesc{};
		resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resdesc.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0xff;
		resdesc.Height = 1;
		resdesc.DepthOrArraySize = 1;
		resdesc.MipLevels = 1;
		resdesc.SampleDesc.Count = 1;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		//�萔�o�b�t�@�̐���
		result = device->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&object->constBuffTransform));
		assert(SUCCEEDED(result));

		//�萔�o�b�t�@�̃}�b�s���O
		result = object->constBuffTransform->Map(0, nullptr, (void**)&object->constMapTransform);
		assert(SUCCEEDED(result));

	}

	void UpdateObject3d(Object3d* object, XMMATRIX& matView, XMMATRIX& matProjection)
	{
		XMMATRIX matScale, matRot, matTrans;

		//�s��̌v�Z
		matScale = XMMatrixScaling(object->scale.x, object->scale.y, object->scale.z);
		matRot = XMMatrixIdentity();
		matRot *= XMMatrixRotationZ(object->rotation.z);
		matRot *= XMMatrixRotationX(object->rotation.x);
		matRot *= XMMatrixRotationY(object->rotation.y);
		matTrans = XMMatrixTranslation(object->position.x, object->position.y, object->position.z);

		//�s��̍���
		object->matWorld = XMMatrixIdentity();
		object->matWorld *= matScale;
		object->matWorld *= matRot;
		object->matWorld *= matTrans;

		if (object->parent != nullptr) {
			object->matWorld *= object->parent->matWorld;
		}
		//�萔�o�b�t�@�փf�[�^�]��
		object->constMapTransform->mat = object->matWorld * matView * matProjection;
	}

	void DrawObject3d(Object3d* object, ID3D12GraphicsCommandList* commandList, D3D12_VERTEX_BUFFER_VIEW& vbView,
		D3D12_INDEX_BUFFER_VIEW& ibView, UINT numIndeces) {
		//���_�o�b�t�@�̐ݒ�
		commandList->IASetVertexBuffers(0, 1, &vbView);
		//�C���f�b�N�X�o�b�t�@�̐ݒ�
		commandList->IASetIndexBuffer(&ibView);
		//�萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
		commandList->SetGraphicsRootConstantBufferView(2, object->constBuffTransform->GetGPUVirtualAddress());

		//�`�惊�X�g
		commandList->DrawIndexedInstanced(numIndeces, 1, 0, 0, 0);
	}
private:
	//3D�I�u�W�F�N�g�̐�
	static const size_t kObjectCount = 1;
	//3D�I�u�W�F�N�g�̔z��
	Object3d object3ds[kObjectCount];
	XMMATRIX matProjection;
	XMMATRIX matview;
	SpriteCommon* spritecommon;
	DirectXCommon* dxCommon;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>CommandList;
	HRESULT result;
	ID3D12Resource* constBuffMaterial = nullptr;
	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�C���f�b�N�X�o�b�t�@�r���[�쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};
	ID3D12DescriptorHeap* srvHeap = nullptr;
};

