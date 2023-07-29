#include "PostEffect.h"
#include"DirectXTex/DirectXTex.h"
#include<d3dcompiler.h>
#include "WinApp.h"
#include <d3dx12.h>

using namespace DirectX;

//インデックスデータ
unsigned short postIndices[] = {
	0,1,2,
	2,1,3,
};

//静的メンバ変数の実態
const float PostEffect::clearColor[4] = { 0.25f,0.5f,0.1f,0.0f };

void PostEffect::Initialize(SpriteCommon* spriteCommon_,uint32_t texIndex)
{
	ID3DBlob* vsBlob = nullptr;
	ID3DBlob* psBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	CD3DX12_HEAP_PROPERTIES heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK,
		D3D12_MEMORY_POOL_L0);
	//テクスチャリソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
		(UINT)WinApp::window_width, (UINT)WinApp::window_height,
		1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
	);


	{
		//変数へコピー
		spriteCommon = spriteCommon_;
		directXCom = spriteCommon_->GetdxCom();

		HRESULT result;
		//Sprite::Initialize(spriteCommon, texIndex);
			//頂点バッファ
		D3D12_HEAP_PROPERTIES heapProp{};//ヒープ設定
		heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPUへの転送
		//リソース設定
		D3D12_RESOURCE_DESC resDesc{};
		resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resDesc.Width = sizeof(Vertex) * 4;
		resDesc.Height = 1;
		resDesc.DepthOrArraySize = 1;
		resDesc.MipLevels = 1;
		resDesc.SampleDesc.Count = 1;
		resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		//頂点バッファの生成
		//ID3D12Resource* vertBuff = nullptr;
		result = directXCom->GetResult();
		result = directXCom->GetDevice()->CreateCommittedResource(
			&heapProp,//ヒープ設定
			D3D12_HEAP_FLAG_NONE,
			&resDesc,//リソース設定
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&vertBuff));
		assert(SUCCEEDED(result));

		//頂点データ
		Vertex vertices[4] = {
			{{-0.5f,-0.5f,0.0f},{0.0f,1.0f}},
			{{-0.5f,+0.5f,0.0f},{0.0f,0.0f}},
			{{+0.5f,-0.5f,0.0f},{1.0f,1.0f}},
			{{+0.5f,+0.5f,0.0f},{1.0f,0.0f}},
		};

		// 頂点バッファへのデータ転送
		Vertex* vertMap = nullptr;
		result = vertBuff->Map(0, nullptr, (void**)&vertMap);
		if (SUCCEEDED(result)) {
			memcpy(vertMap, vertices, sizeof(vertices));
			vertBuff->Unmap(0, nullptr);
		}
		//頂点バッファビューの作成
		//GPU仮想アドレス
		vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
		//頂点バッファのサイズ
		vbView.SizeInBytes = sizeof(Vertex) * 4;
		//頂点1つ分のデータサイズ
		vbView.StrideInBytes = sizeof(Vertex);

		// 定数バッファの設定
		D3D12_HEAP_PROPERTIES cbHeapProp{};   // ヒープ設定
		cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPUへの転送用
		// リソース設定
		D3D12_RESOURCE_DESC cbResourceDesc{};
		cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		cbResourceDesc.Width = (sizeof(ConstBufferData) + 0xff) & ~0xff; // 頂点データ全体のサイズ
		cbResourceDesc.Height = 1;
		cbResourceDesc.DepthOrArraySize = 1;
		cbResourceDesc.MipLevels = 1;
		cbResourceDesc.SampleDesc.Count = 1;
		cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		//定数バッファの生成
		result = directXCom->GetDevice()->CreateCommittedResource(
			&cbHeapProp,//ヒープ設定
			D3D12_HEAP_FLAG_NONE,
			&cbResourceDesc,//リソース設定
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&constBuff));
		assert(SUCCEEDED(result));
	}

	//テクスチャバッファの生成
	CD3DX12_CLEAR_VALUE crealVal = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, clearColor);
	result = directXCom->GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		&crealVal,
		IID_PPV_ARGS(&texBuff));
	assert(SUCCEEDED(result));
	//頂点シェーダーの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/hlsl/SpriteVS.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main", "vs_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&vsBlob, &errorBlob);
	//エラーなら
	if (FAILED(result))
	{
		//errorBlobからエラー内容をstring型にコピー
		std::string error;
		error.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		//エラー内容を出力ウィンドウに表示
		OutputDebugStringA(error.c_str());
		assert(0);
	}
	//ピクセルシェーダーの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/hlsl/SpritePS.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main", "ps_5_0",
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&psBlob, &errorBlob);
	//エラーなら
	if (FAILED(result))
	{
		//errorBlobからエラー内容をstring型にコピー
		std::string error;
		error.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		//エラー内容を出力ウィンドウに表示
		OutputDebugStringA(error.c_str());
		assert(0);
	}
	//頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{
			"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
		},
		{
			"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
		},
	};

	{//テクスチャを赤クリア
		//画素数
		const UINT pixelCount = WinApp::window_width * WinApp::window_height;
		//画像
		const UINT rowPitch = sizeof(UINT) * WinApp::window_width;
		//画像全体のサイズ
		const UINT depthPitch = rowPitch * WinApp::window_height;
		//イメージ
		UINT* img = new UINT[pixelCount];
		for (int i = 0; i < pixelCount; i++) { 
			img[i] = 0xff0000ff; 
		}

		//テクスチャバッファにデータ転送
		result = texBuff->WriteToSubresource(0, nullptr, img, rowPitch, depthPitch);
		assert(SUCCEEDED(result));
		delete[] img;
	}
	incrementSize = directXCom->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	CreateHeaps();
}

void PostEffect::Draw(ID3D12GraphicsCommandList* comList)
{
	comList = directXCom->GetCommandList();
	//matWorld = XMMatrixIdentity();
	//matWorld *= XMMatrixRotationZ(XMConvertToRadians(rotation));
	//matWorld *= XMMatrixTranslation(position.x, position.y, 0.0f);

	constMap->color = color;
	constMap->mat = XMMatrixIdentity();

	//非表示
	if (isInvisible)
	{
		return;
	}

	SetTextureCommands(texIndex);

	// 頂点バッファビューの設定コマンド
	comList->IASetVertexBuffers(0, 1, &vbView);
	//定数バッファビュー（CBV）の設定コマンド
	comList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());

	//インディックスバッファビューの設定コマンド
	comList->IASetIndexBuffer(&ibView);
	//定数バッファビュー(CBV)の設定コマンド
	//comList->SetGraphicsRootConstantBufferView(2, constBuff->GetGPUVirtualAddress());
	// 描画コマンド
	comList->DrawIndexedInstanced(_countof(postIndices), 1, 0, 0, 0);//全ての頂点を使って描画
}

void PostEffect::SetTextureCommands(uint32_t index)
{
	comList = directXCom->GetCommandList();
	// パイプラインステートとルートシグネチャの設定コマンド
	comList->SetPipelineState(spriteCommon->GetPipeline());
	comList->SetGraphicsRootSignature(spriteCommon->GetRootSignature());

	// プリミティブ形状の設定コマンド
	comList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
	//三角形リスト		TRIANGLELIST
	//三角形ストリップ	TRIANGLESTRIP
	//線リスト			LINELIST
	//線ストリップ		LINESTRIP
	//点リスト			POINTLIST
	//SRVヒープの設定コマンド
	comList->SetDescriptorHeaps(1, &descHeapSRV);
	//SRVヒープの先頭ハンドルを取得（SRVを指しているはず）
	D3D12_GPU_DESCRIPTOR_HANDLE	srvGpuHandle = descHeapSRV->GetGPUDescriptorHandleForHeapStart();
	//SRVヒープの先頭にあるSRVをルートパラメータ１番に設定
	//srvGpuHandle.ptr = 0;
	for (size_t i = 0; i < index; i++)
	{
		srvGpuHandle.ptr += incrementSize;
	}
	comList->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
}

void PostEffect::PreDrawScene(ID3D12GraphicsCommandList* cmdList)
{
	//リソースバリア
	CD3DX12_RESOURCE_BARRIER resBarrier = CD3DX12_RESOURCE_BARRIER::Transition(texBuff.Get(),
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		D3D12_RESOURCE_STATE_RENDER_TARGET);
	//ビューポート
	CD3DX12_VIEWPORT viewPort = CD3DX12_VIEWPORT(0.0f, 0.0f,
		WinApp::window_width, WinApp::window_height);



	//リソースバリアを変更
	cmdList->ResourceBarrier(1,
		&resBarrier);
	//レンダーターゲットビュー用ディスクリプタヒープのハンドル取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvH =
		descHeapRTV->GetCPUDescriptorHandleForHeapStart();
	//深度ステンシルビュー用デスクリプタヒープのハンドル取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvH =
		descHeapDSV->GetCPUDescriptorHandleForHeapStart();
	//レンダーターゲットをセット
	cmdList->OMSetRenderTargets(1, &rtvH, false, &dsvH);

	//ビューポートの設定
	cmdList->RSSetViewports(1, &viewPort);
	//シザリング矩形の設定
	CD3DX12_RECT rect = CD3DX12_RECT(0, 0, WinApp::window_width,
		WinApp::window_height);
	cmdList->RSSetScissorRects(1, &rect);

	//全画面クリア
	cmdList->ClearRenderTargetView(rtvH, clearColor, 0, nullptr);
	//深度バッファのクリア
	cmdList->ClearDepthStencilView(dsvH, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0,
		nullptr);
}

void PostEffect::PostDrawScene(ID3D12GraphicsCommandList* cmdList)
{
	CD3DX12_RESOURCE_BARRIER resBarrier = CD3DX12_RESOURCE_BARRIER::Transition(texBuff.Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
	//リソースバッファを変更
	cmdList->ResourceBarrier(1, &resBarrier);

}

void PostEffect::CreateHeaps()
{
	//デスクリプタヒープ生成
	D3D12_DESCRIPTOR_HEAP_DESC srvDescHeapDesc = {};
	srvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvDescHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	srvDescHeapDesc.NumDescriptors = 1;

	result = directXCom->GetDevice()->CreateDescriptorHeap(&srvDescHeapDesc, IID_PPV_ARGS(&descHeapSRV));
	assert(SUCCEEDED(result));

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	//デスクリプタヒープにSRV作成
	directXCom->GetDevice()->CreateShaderResourceView(texBuff.Get(),
		&srvDesc,
		descHeapSRV->GetCPUDescriptorHandleForHeapStart()
	);

	//RTV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeapDesc{};
	rtvDescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDescHeapDesc.NumDescriptors = 1;
	//RTV用デスクリプタヒープ生成
	result = directXCom->GetDevice()->CreateDescriptorHeap(&rtvDescHeapDesc, IID_PPV_ARGS(&descHeapRTV));
	assert(SUCCEEDED(result));

	//レンダーターゲットビュー設定
	D3D12_RENDER_TARGET_VIEW_DESC renderTargetViewDesc{};
	//シェーダーの計算結果をSRGBに変換書き込み
	renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	renderTargetViewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

	//デスクリプタヒープにRTV作成
	directXCom->GetDevice()->CreateRenderTargetView(texBuff.Get(),
		&renderTargetViewDesc,
		descHeapRTV->GetCPUDescriptorHandleForHeapStart()
	);
	//深度バッファリソース
	CD3DX12_RESOURCE_DESC depthResDesc =
		CD3DX12_RESOURCE_DESC::Tex2D(
			DXGI_FORMAT_D32_FLOAT,
			WinApp::window_width,
			WinApp::window_height,
			1, 0,
			1, 0,
			D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
		);

	CD3DX12_HEAP_PROPERTIES heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	CD3DX12_CLEAR_VALUE clearValue = CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT, 1.0f, 0);
	//深度バッファ生成
	result = directXCom->GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&depthResDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&clearValue,
		IID_PPV_ARGS(&depthBuff));
	assert(SUCCEEDED(result));
	//DSV用デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC DescHeapDesc{};
	DescHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	DescHeapDesc.NumDescriptors = 1;
	//DSV用デスクリプタヒープを作成
	result = directXCom->GetDevice()->CreateDescriptorHeap(&DescHeapDesc, IID_PPV_ARGS(&descHeapDSV));
	assert(SUCCEEDED(result));

	//デスクリプタヒープにDSV作成
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;//深度値フォーマット
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	directXCom->GetDevice()->CreateDepthStencilView(depthBuff.Get(),
		&dsvDesc,
		descHeapDSV->GetCPUDescriptorHandleForHeapStart());
}
