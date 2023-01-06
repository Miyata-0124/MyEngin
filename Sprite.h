#pragma once
#include "SpriteCommon.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
using namespace DirectX;

//スプライトの部分
class Sprite
{
public:
	void Initialize(SpriteCommon* spriteCommon_);
	void Update();
	void Draw();

private: //構造体
	//定数バッファ用データ構造体
	struct ConstBufferDataTransform {
		XMMATRIX mat;//3D変換行列
	};

	// 3Dオブジェクト型
	struct Object3d
	{
		//定数バッファ
		ID3D12Resource* constBuffTransform;
		//定数バッファマップ
		ConstBufferDataTransform* constMapTransform;
		//アフィン変換
		XMFLOAT3 scale = { 1,1,1 };
		XMFLOAT3 rotation = { 0,0,0 };
		XMFLOAT3 position = { 0,0,0 };
		//ワールド変換行列
		XMMATRIX matWorld;
		//親オブジェクトへのポイント
		Object3d* parent = nullptr;
	};

	void InitializeObject3d(Object3d* object, ID3D12Device* device)
	{
		HRESULT result;

		//定数バッファのヒープ設定
		D3D12_HEAP_PROPERTIES heapProp{};
		heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
		//定数バッファのリソース
		D3D12_RESOURCE_DESC resdesc{};
		resdesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resdesc.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0xff;
		resdesc.Height = 1;
		resdesc.DepthOrArraySize = 1;
		resdesc.MipLevels = 1;
		resdesc.SampleDesc.Count = 1;
		resdesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		//定数バッファの生成
		result = device->CreateCommittedResource(
			&heapProp,
			D3D12_HEAP_FLAG_NONE,
			&resdesc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&object->constBuffTransform));
		assert(SUCCEEDED(result));

		//定数バッファのマッピング
		result = object->constBuffTransform->Map(0, nullptr, (void**)&object->constMapTransform);
		assert(SUCCEEDED(result));

	}

	void UpdateObject3d(Object3d* object, XMMATRIX& matView, XMMATRIX& matProjection)
	{
		XMMATRIX matScale, matRot, matTrans;

		//行列の計算
		matScale = XMMatrixScaling(object->scale.x, object->scale.y, object->scale.z);
		matRot = XMMatrixIdentity();
		matRot *= XMMatrixRotationZ(object->rotation.z);
		matRot *= XMMatrixRotationX(object->rotation.x);
		matRot *= XMMatrixRotationY(object->rotation.y);
		matTrans = XMMatrixTranslation(object->position.x, object->position.y, object->position.z);

		//行列の合成
		object->matWorld = XMMatrixIdentity();
		object->matWorld *= matScale;
		object->matWorld *= matRot;
		object->matWorld *= matTrans;

		if (object->parent != nullptr) {
			object->matWorld *= object->parent->matWorld;
		}
		//定数バッファへデータ転送
		object->constMapTransform->mat = object->matWorld * matView * matProjection;
	}

	void DrawObject3d(Object3d* object, ID3D12GraphicsCommandList* commandList, D3D12_VERTEX_BUFFER_VIEW& vbView,
		D3D12_INDEX_BUFFER_VIEW& ibView, UINT numIndeces) {
		//頂点バッファの設定
		commandList->IASetVertexBuffers(0, 1, &vbView);
		//インデックスバッファの設定
		commandList->IASetIndexBuffer(&ibView);
		//定数バッファビュー(CBV)の設定コマンド
		commandList->SetGraphicsRootConstantBufferView(2, object->constBuffTransform->GetGPUVirtualAddress());

		//描画リスト
		commandList->DrawIndexedInstanced(numIndeces, 1, 0, 0, 0);
	}
private:
	//3Dオブジェクトの数
	static const size_t kObjectCount = 1;
	//3Dオブジェクトの配列
	Object3d object3ds[kObjectCount];
	XMMATRIX matProjection;
	XMMATRIX matview;
	SpriteCommon* spritecommon;
	DirectXCommon* dxCommon;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>CommandList;
	HRESULT result;
	ID3D12Resource* constBuffMaterial = nullptr;
	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//インデックスバッファビュー作成
	D3D12_INDEX_BUFFER_VIEW ibView{};
	ID3D12DescriptorHeap* srvHeap = nullptr;
};

