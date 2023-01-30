
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
#define DIRECTINPUT_VERSION 0x0800 //DirectInputのバージョン指定
#include <dinput.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

//Windowsアプリでのエントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//コンソールへの文字出力
	OutputDebugStringA("Hello,Directx!!\n");

	MSG msg{};	//メッセージ

	//DirectX初期化処理ここから
#ifdef  _DEBUG
	//デバッグレイヤーをオンに
	ID3D12Debug* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
	}
#endif //  _DEBUG
#pragma region 初期化DirectX

	WinApp* winApp = nullptr;
	// WindowsAPIの初期化
	winApp = new WinApp();
	winApp->Initialize();

	DirectXCommon* dxCommon = nullptr;
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	Input* input = nullptr;
	input = new Input();
	input->Initialize(winApp);
#pragma endregion
	//DirectX初期化処理ここまで
	//描画初期化処理
	SpriteCommon* spriteCommon = nullptr;
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	Sprite* sprite = nullptr;
	sprite = new Sprite;
	sprite->Initialize(spriteCommon);
	
	
	
	//////射影変換行列の計算
	//XMMATRIX matProjection =
	//	XMMatrixPerspectiveFovLH(
	//		XMConvertToRadians(45.0f),//上下画角45度
	//		(float)WinApp::window_width / WinApp::window_height,//アスペクト比(画面横幅/画面縦幅)
	//		0.1f, 1000.0f//前端,奥端
	//	);
	//////ビュー変換行列を計算
	//XMMATRIX matview;
	//XMFLOAT3 eye(0, 0, -100);	//始点座標
	//XMFLOAT3 target(0, 0, 0);	//注視点座標
	//XMFLOAT3 up(0, 1, 0);		//上方向ベクトル
	//matview = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

#pragma region 画像データ
#pragma region リソースデータ作成
	////横方向ピクセル数
	//const size_t textureWidth = 256;
	////縦方向ピクセル数
	//const size_t textureHeight = 256;
	////配列の要素数
	//const size_t imageDataCount = textureWidth * textureHeight;
	////画像イメージデータ
	//XMFLOAT4* imageData = new XMFLOAT4[imageDataCount];//必ず解放

	////全ピクセルの色を初期化
	//for (size_t i = 0; i < imageDataCount; i++) {
	//	imageData[i].x = 1.0f; //R
	//	imageData[i].y = 0.0f; //G
	//	imageData[i].z = 0.0f; //B
	//	imageData[i].w = 1.0f; //A
	//}
	////元データ解放
	//delete[] imageData;
#pragma endregion
//	TexMetadata metadata{};
//	ScratchImage scratchImg{};
//	//WICテクスチャのロード
//	result = LoadFromWICFile(
//		L"Resource/test.png",
//		WIC_FLAGS_NONE,
//		&metadata, scratchImg
//	);
//	ScratchImage mipChain{};
//	//ミニマップ生成
//	result = GenerateMipMaps(
//		scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(),
//		TEX_FILTER_DEFAULT, 0, mipChain);
//	if (SUCCEEDED(result)) {
//		scratchImg = std::move(mipChain);
//		metadata = scratchImg.GetMetadata();
//	}
//	//読み込んだディヒューズテクスチャをSRGBとして使う
//	metadata.format = MakeSRGB(metadata.format);
//	//ヒープ設定
//	D3D12_HEAP_PROPERTIES textureHeapProp{};
//	textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
//	textureHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
//	textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
//	//リソース設定
//	D3D12_RESOURCE_DESC textureResourceDesc{};
//	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
//	textureResourceDesc.Format = metadata.format;
//	textureResourceDesc.Width = metadata.width; //幅
//	textureResourceDesc.Height = metadata.height; //高さ
//	textureResourceDesc.DepthOrArraySize = (UINT)metadata.arraySize;
//	textureResourceDesc.MipLevels = (UINT)metadata.mipLevels;
//	textureResourceDesc.SampleDesc.Count = 1;
//
//	//テクスチャバッファの生成
//	ID3D12Resource* texBuff = nullptr;
//	result = dxCommon->GetDevice()->CreateCommittedResource(
//		&textureHeapProp,
//		D3D12_HEAP_FLAG_NONE,
//		&textureResourceDesc,
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&texBuff));
//
//	//全ミニマップについて
//	for (size_t i = 0; i < metadata.mipLevels; i++) {
//		//ミニマップレベルを指定してイメージを取得
//		const Image* img = scratchImg.GetImage(i, 0, 0);
//		//テクスチャバッファにデータ転送
//		result = texBuff->WriteToSubresource(
//			(UINT)i,
//			nullptr,				//全領域へコピー
//			img->pixels,			//元データアドレス
//			(UINT)img->rowPitch,	//1ラインサイズ
//			(UINT)img->slicePitch	//1枚サイズ
//		);
//		assert(SUCCEEDED(result));
//	}
//
//	//SRVの最大個数
//	const size_t kMaxSRVCount = 2056;
//
//	//デスクリプタヒープの設定
//	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc{};
//	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
//	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダーから見えるように
//	srvHeapDesc.NumDescriptors = kMaxSRVCount;
//
//	//設定を元にSRV用デスクリプタヒープを生成
//	ID3D12DescriptorHeap* srvHeap = nullptr;
//	result = dxCommon->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvHeap));
//	assert(SUCCEEDED(result));
//
//	//SRVヒープの先頭ハンドル取得
//	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();
//
//	//シェーダリソースビュー
//	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; //設定構造体
//	srvDesc.Format = resDesc.Format; //RGBA float
//	srvDesc.Shader4ComponentMapping =
//		D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
//	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; //2Dテクスチャ
//	srvDesc.Texture2D.MipLevels = resDesc.MipLevels;
//
//	//ハンドルの指す位置にシェーダーリソースビュー作成
//	dxCommon->GetDevice()->CreateShaderResourceView(texBuff, &srvDesc, srvHandle);
//
//	//デスクリプタレンジの設定
//	D3D12_DESCRIPTOR_RANGE descriptorRange{};
//	descriptorRange.NumDescriptors = 1; //1度に描画に使うテクスチャが1枚なので1
//	descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
//	descriptorRange.BaseShaderRegister = 0; //テクスチャレジスタ0番
//	descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
//#pragma endregion
//
//
//	//値を書き込むと自動に転送される
//	constMapMaterial->color = XMFLOAT4(1, 1, 1, 1);//色
	
	
	
	
#pragma region 深度バッファ
	////リソース設定
	//D3D12_RESOURCE_DESC depthResourceDesc{};
	//depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	//depthResourceDesc.Width = WinApp::window_width; // レンダーターゲットに合わせる
	//depthResourceDesc.Height = WinApp::window_height; // レンダーターゲットに合わせる
	//depthResourceDesc.DepthOrArraySize = 1;
	//depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT; // 深度値フォーマット
	//depthResourceDesc.SampleDesc.Count = 1;
	//depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL; // デプスステンシル
	////深度値用ヒーププロパティ
	//D3D12_HEAP_PROPERTIES depthHeapProp{};
	//depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	////深度値のクリア設定
	//D3D12_CLEAR_VALUE depthClearValue{};
	//depthClearValue.DepthStencil.Depth = 1.0f; // 深度値1.0f(最大値)でクリア
	//depthClearValue.Format = DXGI_FORMAT_D32_FLOAT; //深度値フォーマット
	////リソース生成
	//ID3D12Resource* depthBuff = nullptr;
	//result = dxCommon->GetDevice()->CreateCommittedResource(
	//	&depthHeapProp,
	//	D3D12_HEAP_FLAG_NONE,
	//	&depthResourceDesc,
	//	D3D12_RESOURCE_STATE_DEPTH_WRITE, // 深度値書き込みに使用
	//	&depthClearValue,
	//	IID_PPV_ARGS(&depthBuff));
	////深度ビュー用デスクリプタヒープ生成
	//D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	//dsvHeapDesc.NumDescriptors = 1; // 深度ビューは1つ
	//dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // デプスステンシルビュー
	//ID3D12DescriptorHeap* dsvHeap = nullptr;
	//result = dxCommon->GetDevice()->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));
	////深度ビュー作成
	//D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	//dsvDesc.Format = DXGI_FORMAT_D32_FLOAT; // 深度値フォーマット
	//dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	//dxCommon->GetDevice()->CreateDepthStencilView(
	//	depthBuff,
	//	&dsvDesc,
	//	dsvHeap->GetCPUDescriptorHandleForHeapStart());
	////デプスステンシルステート設定
	//pipelineDesc.DepthStencilState.DepthEnable = true; // 深度テストを行う
	//pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // 書き込み許可
	//pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // 小さければ合格
	//pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT; // 深度値フォーマット

#pragma endregion



#pragma region ブレンド合成

	// 加算合成
	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;//加算(上とは別)
	//blenddesc.SrcBlend = D3D12_BLEND_ONE;//ソースの値を100%使う
	//blenddesc.DestBlend = D3D12_BLEND_ONE;//テストの値を100%使う
	// 減算合成
	//blenddesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;//減算(上とは別)
	//blenddesc.SrcBlend = D3D12_BLEND_ONE;//ソースの値を100%使う
	//blenddesc.DestBlend = D3D12_BLEND_ONE;//テストの値を100%使う
	// 色反転
	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;//加算(上とは別)
	//blenddesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR;//ソースの値を100%使う
	//blenddesc.DestBlend = D3D12_BLEND_ZERO;//テストの値を100%使う
	// 半透明合成
	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD;//加算(上とは別)
	//blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;//ソースの値を100%使う
	//blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;//テストの値を100%使う
#pragma endregion
	

	
	
#pragma region テクスチャサンプラーの設定
	//D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	//samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; //横繰り返し (タイリング)
	//samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP; //縦繰り返し (タイリング)
	//samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP; //奥行繰り返し (タイリング)
	//samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK; //ボーダーの時は黒
	//samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR; //全てのリニア補間
	//samplerDesc.MaxLOD = D3D12_FLOAT32_MAX; //ミニマップ最大値
	//samplerDesc.MinLOD = 0.0f; //ミニマップ最大値
	//samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	//samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; //ピクセルシェーダからのみ使用可能
#pragma endregion
	
	

	float angle = 0.0f; //カメラの回転角

	//ゲームループ
	while (true)
	{
		//メッセージ処理
		if (winApp->ProcessMessage()) {
			//ゲームループを抜ける
			break;
		}

		//DirectX毎フレーム処理　ここから
		input->Update();

		//描画前処理
		dxCommon->PreDraw();
		spriteCommon->Update();
		////定数バッファビュー(CBV)の設定コマンド
		//dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetGPUVirtualAddress());

		////SRVヒープの設定コマンド
		//dxCommon->GetCommandList()->SetDescriptorHeaps(1, &srvHeap);
		////SRVヒープの先頭ハンドルを取得(SRVを指定しているはず)
		//D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();
		////SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
		//dxCommon->GetCommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
		////インデックスバッファビューの設定コマンド
		//dxCommon->GetCommandList()->IASetIndexBuffer(&ibView);

		//描画後処理
		dxCommon->PostDraw();
		//DirectX枚フレーム処理　ここまで
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