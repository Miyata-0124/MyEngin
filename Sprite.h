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
private:
	SpriteCommon* spriteCommon;
	DirectXCommon* dxCommon;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>CommandList;
	HRESULT result;
	//頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};
};

