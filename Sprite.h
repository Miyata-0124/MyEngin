#pragma once //スプライト1枚分
#include "SpriteCommon.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
using namespace DirectX;

class Sprite
{
public: // メンバ関数
	// 初期化
	void Initialize(SpriteCommon* spriteCommon_);
	void Draw();

private: // 構造体
	struct ConstBufferDataMaterial
	{
		XMFLOAT4 color;
	};

	struct Vertex
	{
		XMFLOAT3 pos; //xyz座標
		XMFLOAT2 uv; // uv座標
	};
	//頂点データ
	Vertex vertices[4] = {
		{{-0.4f,-0.7f,0.0f},{0.0f,1.0f}},// 左下
		{{-0.4f,+0.7f,0.0f},{0.0f,0.0f}},// 左上
		{{+0.4f,-0.7f,0.0f},{1.0f,1.0f}},// 右下
		{{+0.4f,+0.7f,0.0f},{1.0f,0.0f}},// 右上
	};

private:
	DirectXCommon* dxCommon;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>CommandList;
	HRESULT result;
	//頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{}; 
	ID3D12Resource* constBuffMaterial;
};

