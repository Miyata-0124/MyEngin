#pragma once
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include <d3d12.h>
#include <string>
#include <wrl.h>
#include <array>
using namespace DirectX;
using namespace Microsoft::WRL;

#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

class SpriteCommon
{
public:
	void Initialize(DirectXCommon* dxCommon);

	void Update(DirectXCommon* dxCommon);

	//テクスチャ読み込み
	void LoadTexture(uint32_t index, const std::string& fileName);

	//描画用テクスチャコマンドの発行
	void SetTextureCommands(uint32_t index);

	//描画前処理
	void PreDraw();

	//描画後処理
	void PostDraw();

	//ゲッター
	DirectXCommon* GetDirectXCommon() const { return dxCommon; }
	ComPtr<ID3D12Resource> GetTextureBuffer(uint32_t index) const { return textureBuffers_[index].Get(); }

private:
	HRESULT result;
	DirectXCommon* dxCommon = nullptr;

	ComPtr<ID3DBlob> vsBlob;//頂点シェーダオブジェクト
	/*頂点シェーダ・・・頂点座標を変換するのが役割
	モデルデータ（用意した頂点データ）の一点ずつに対して、頂点データのプログラムが一回実行される*/
	ComPtr<ID3DBlob> psBlob;//ピクセルシェーダオブジェクト
	/*ピクセルシェーダ・・・描画色の設定が役割
	ラスタライザが分解した後の１ピクセルずつに対して、ピクセルシェーダのプログラムが一回実行される*/
	ComPtr<ID3DBlob> errorBlob;//エラーオブジェクト

	//グラフィックスパイプライン設定
	/*グラフィックスパイプライン・・・DirectXに限らず、CG描画の一般的な手法
	ポリゴンを描画するときの流れ*/
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	//ルートシグネチャ
	/*ルートパラメータの設定をオブジェクト化したもの*/
	ComPtr<ID3D12RootSignature> rootSignature;
	//ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	//ルートシグネチャのシリアライズ
	ComPtr<ID3DBlob> rootSigBlob;
	//パイプラインステートの生成
	ComPtr<ID3D12PipelineState> pipelineState;

	//SRVの最大個数
	static const size_t kMaxSRVCount = 2056;
	//テクスチャバッファ
	/*バッファ・・・複数の主体がデータを送受信する際に、処理速度や転送速度の差、タイミングのズレなどを補うためにデータを一時的に蓄えておく記憶装置や記憶領域のこと*/
	std::array<ComPtr<ID3D12Resource>, kMaxSRVCount> textureBuffers_;

	//設定を元にSRV用デスクリプタヒープを生成
	ComPtr<ID3D12DescriptorHeap> srvHeap;

	//デフォルトテクスチャ格納ディレクトリ
	static std::string kDefaultTextureDirectoryPath;

};
