#pragma once
#include "SpriteCommon.h"

class Sprite
{
public:
	//定数バッファ用データ構造体(マテリアル)
	/*定数バッファ・・・CPUで動くプログラムの変数群を、GPUで動くプログラマブルシェーダーに定数群（バッファ）として送り込む機構*/
	struct ConstBufferDataMaterial {
		XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f }; //色(RGBA)
	};

	//定数バッファ用データ構造体(3D変換行列)
	struct ConstBufferDataTransform {
		XMMATRIX mat;	//3D変換行列
	};

	struct Vertex {
		XMFLOAT3 pos;	//xyz座標
		XMFLOAT2 uv;	//uv座標
	};

	void Initialize(SpriteCommon* spriteCommon);

	void Update(SpriteCommon* spriteCommon);

	void Draw(SpriteCommon* spriteCommon);

	//セッター
	void SetPosition(const XMFLOAT2& position) { position_ = position; }
	void SetSize(const XMFLOAT2& size) { size_ = size; }
	void SetRotation(const float& rotation) { rotation_.z = rotation; }
	void SetColor(const XMFLOAT4& color) { color_ = color; }
	void SetIndex(const uint32_t textureIndex) { textureIndex_ = textureIndex; }
	//void SetTextureSize(const XMFLOAT2 textureSize) { textureSize_ = textureSize; }
	//ゲッター
	const XMFLOAT2& GetPosition() const { return position_; }
	const XMFLOAT2& GetSize() const { return size_; }
	const float& GetRotation() const { return rotation_.z; }
	const XMFLOAT4& GetColor() const { return color_; }
	const uint32_t GetTextureIndex() const { return textureIndex_; }
	//const XMFLOAT2 GetTextureSize() const { return textureSize_; }

private:
	//頂点番号
	enum VertexNumber {
		LB,//左下
		LT,//左上
		RB,//右下
		RT,//右上
	};

	HRESULT result;

	//スケーリング倍率
	XMFLOAT3 scale;
	//回転角
	XMFLOAT3 rotation_;
	//座標
	XMFLOAT2 position_;
	//色
	XMFLOAT4 color_ = { 1, 1, 1, 1 };
	//表示サイズ
	XMFLOAT2 size_ = { 100.0f, 100.0f };

	//頂点データ
	Vertex vertices[4] = {
		{{-0.0f,100.0f,0.0f},{0.0f,1.0f}},//左下
		{{-0.0f,+0.0f,0.0f},{0.0f,0.0f}},//左上
		{{100.0f,100.0f,0.0f},{1.0f,1.0f}},//右下
		{{100.0f,-0.0f,0.0f},{1.0f,0.0f}},//右上
	};

	//テクスチャ左上座標
	//XMFLOAT2 textureLeftTop_ = { 0.0f,0.0f };
	//テクスチャ切り出しサイズ
	//XMFLOAT2 textureSize_ = { 100.0f,100.0f };

	//頂点データ全体のサイズ = 頂点データ一つ分のサイズ * 頂点データの要素数
	UINT sizeVB = static_cast<UINT>(sizeof(vertices[0]) * _countof(vertices));

	//頂点バッファの設定
	/*頂点バッファ・・・頂点データ用のバッファ*/
	D3D12_HEAP_PROPERTIES heapProp{};//ヒープ設定

	//リソース設定
	D3D12_RESOURCE_DESC resDesc{};

	ComPtr<ID3D12Resource> vertBuff;

	Vertex* vertMap = nullptr;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	//定数バッファの生成
	/*定数バッファ・・・全ピクセル共通のデータを送るときに利用するバッファ*/
	ComPtr<ID3D12Resource> constBuffMaterial;

	//定数バッファ(行列用)
	ComPtr<ID3D12Resource> constBuffTransform;

	//定数バッファマップ(行列用)
	ConstBufferDataTransform* constMapTransform = nullptr;

	ConstBufferDataMaterial* constMapMaterial = nullptr;

	//テクスチャ番号
	uint32_t textureIndex_ = 0;

	SpriteCommon* spriteCommon_;

private:
	//テクスチャサイズをイメージに合わせる
	void AdjustTextrueSize();
};