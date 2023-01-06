#include "Sprite.h"

//定数バッファ用データ構造体(マテリアル)
struct ConstBufferDataMaterial {
	XMFLOAT4 color;//色(RGBA)
};


// 頂点データ構造体
struct Vertex
{
	XMFLOAT3 pos; //xyz座標
	XMFLOAT3 normal; //法線ベクトル
	XMFLOAT2 uv; //uv座標
};
// 頂点データ
Vertex vertices[] = {
	//{	x	  y	   z}	法線 { u	v }
	// 前
	{{-5.0f,-5.0f,-5.0f},{},{0.0f,1.0f}},//左下
	{{-5.0f, 5.0f,-5.0f},{},{0.0f,0.0f}},//左上
	{{ 5.0f,-5.0f,-5.0f},{},{1.0f,1.0f}},//右下
	{{ 5.0f, 5.0f,-5.0f},{},{1.0f,0.0f}},//右上
	// 後				
	{{-5.0f,-5.0f, 5.0f},{},{0.0f,1.0f}},//左下
	{{-5.0f, 5.0f, 5.0f},{},{0.0f,0.0f}},//左上
	{{ 5.0f,-5.0f, 5.0f},{},{1.0f,1.0f}},//右下
	{{ 5.0f, 5.0f, 5.0f},{},{1.0f,0.0f}},//右上
	// 左				,
	{{-5.0f,-5.0f,  5.0f},{},{0.0f,1.0f}},//左下
	{{-5.0f, 5.0f,  5.0f},{},{0.0f,0.0f}},//左上
	{{-5.0f,-5.0f, -5.0f},{},{1.0f,1.0f}},//右下
	{{-5.0f, 5.0f, -5.0f},{},{1.0f,0.0f}},//右上
	// 右
	{{ 5.0f,-5.0f, -5.0f},{},{0.0f,1.0f}},//左下
	{{ 5.0f, 5.0f, -5.0f},{},{0.0f,0.0f}},//左上
	{{ 5.0f,-5.0f,  5.0f},{},{1.0f,1.0f}},//右下
	{{ 5.0f, 5.0f,  5.0f},{},{1.0f,0.0f}},//右上
	// 下
	{{-5.0f,-5.0f, -5.0f},{},{0.0f,1.0f}},//左下
	{{-5.0f,-5.0f,  5.0f},{},{0.0f,0.0f}},//左上
	{{ 5.0f,-5.0f, -5.0f},{},{1.0f,1.0f}},//右下
	{{ 5.0f,-5.0f,  5.0f},{},{1.0f,0.0f}},//右上
	// 上
	{{-5.0f, 5.0f, -5.0f},{},{0.0f,1.0f}},//左下
	{{-5.0f, 5.0f,  5.0f},{},{0.0f,0.0f}},//左上
	{{ 5.0f, 5.0f, -5.0f},{},{1.0f,1.0f}},//右下
	{{ 5.0f, 5.0f,  5.0f},{},{1.0f,0.0f}},//右上
};
// 頂点データ全体のサイズ = 頂点データ一つ分のサイズ * 頂点データの要素数
UINT sizeVB = static_cast<UINT>(sizeof(vertices[0]) * _countof(vertices));
unsigned short indices[] =
{
	// 前
	0,1,2, //三角形１
	2,1,3, //三角形２
	// 後
	4,6,5, //三角形3
	5,6,7, //三角形4
	// 左
	8,9,10, //三角形5
	10,9,11, //三角形6
	// 右
	12,13,14, //三角形7
	14,13,15, //三角形8
	// 下
	16,18,17, //三角形9
	17,18,19, //三角形10
	// 上
	20,21,22, //三角形11
	22,21,23, //三角形12
};

void Sprite::Initialize(SpriteCommon* spriteCommon_)
{
	spritecommon = spriteCommon_;
	dxCommon = spritecommon->GetDxCommon();
	result = dxCommon->GetResult();
	//法線の計算
	for (int i = 0; i < _countof(indices) / 3; i++)
	{//三角形1つごとに計算していく
		//三角形のインデックスを取り出し,一時的な変数に入れる
		unsigned short index0 = indices[i * 3 + 0];
		unsigned short index1 = indices[i * 3 + 1];
		unsigned short index2 = indices[i * 3 + 2];
		//三角形を構成する頂点座標ベクトルに代入
		XMVECTOR p0 = XMLoadFloat3(&vertices[index0].pos);
		XMVECTOR p1 = XMLoadFloat3(&vertices[index1].pos);
		XMVECTOR p2 = XMLoadFloat3(&vertices[index2].pos);
		//p0->p1ベクトル.p0->p2ベクトルを計算 (ベクトル計算)
		XMVECTOR v1 = XMVectorSubtract(p1, p0);
		XMVECTOR v2 = XMVectorSubtract(p2, p0);
		//外積は両方から垂直なベクトル
		XMVECTOR normal = XMVector3Cross(v1, v2);
		//正規化(長さを1にする)
		normal = XMVector3Normalize(normal);
		//求めた法線を頂点データに代入
		XMStoreFloat3(&vertices[index0].normal, normal);
		XMStoreFloat3(&vertices[index1].normal, normal);
		XMStoreFloat3(&vertices[index2].normal, normal);
	}

	// 頂点バッファの設定
	D3D12_HEAP_PROPERTIES heapProp{}; // ヒープ設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPUへの転送用
	// リソース設定
	D3D12_RESOURCE_DESC resDesc{};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB; // 頂点データ全体のサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	// 頂点バッファの生成
	ID3D12Resource* vertBuff = nullptr;

	result = dxCommon->GetDevice()->CreateCommittedResource(
		&heapProp, // ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&resDesc, // リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));
	assert(SUCCEEDED(result));
	// GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
	Vertex* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	// 全頂点に対して
	for (int i = 0; i < _countof(vertices); i++) {
		vertMap[i] = vertices[i]; // 座標をコピー
	}
	// 繋がりを解除
	vertBuff->Unmap(0, nullptr);
	
	// GPU仮想アドレス
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	// 頂点バッファのサイズ
	vbView.SizeInBytes = sizeVB;
	// 頂点1つ分のデータサイズ
	vbView.StrideInBytes = sizeof(vertices[0]);

	//ヒープ設定
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPUへの転送用
	//リソース設定
	D3D12_RESOURCE_DESC cbResourceDesc{};
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferDataMaterial) + 0xff) & ~0xff;//256バイトアライメント
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//定数バッファ
	ID3D12Resource* constBuffTransform0 = nullptr;
	ConstBufferDataTransform* constMapTransform0 = nullptr;

	{
		//ヒープ設定
		D3D12_HEAP_PROPERTIES cbHeapProp{};
		cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPUへの転送用
		//リソース設定
		D3D12_RESOURCE_DESC cbResourceDesc{};
		cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		cbResourceDesc.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0xff;//256バイトアライメント
		cbResourceDesc.Height = 1;
		cbResourceDesc.DepthOrArraySize = 1;
		cbResourceDesc.MipLevels = 1;
		cbResourceDesc.SampleDesc.Count = 1;
		cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	}
	//インデックスデータ全体のサイズ
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * _countof(indices));
	//リソース設定
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB; //インデックス情報が入る分のサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//インデックスバッファの生成
	ID3D12Resource* indexBuff = nullptr;
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&heapProp, //ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&resDesc, //リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff));

	//インデックスバッファをマッピング
	uint16_t* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	//全インデックスに対して
	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i]; //インデックスをコピー
	}
	//マッピング解除
	indexBuff->Unmap(0, nullptr);

	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;

	//定数バッファの生成
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&cbHeapProp,//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc,//リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffMaterial));
	assert(SUCCEEDED(result));
	//定数バッファのマッピング
	ConstBufferDataMaterial* constMapMaterial = nullptr;
	result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial);//マッピング
	assert(SUCCEEDED(result));

	for (int i = 0; i < _countof(object3ds); i++) {
		//初期化
		InitializeObject3d(&object3ds[i], dxCommon->GetDevice());

		//親子構造のサンプル
		if (i > 0) {
			//1つ前のオブジェクトを親オブジェクトとする
			object3ds[i].parent = &object3ds[i - 1];
			//親オブジェクトの9割の大きさ
			object3ds[i].scale = { 0.9f,0.9f,0.9f };
			//親オブジェクトに対してz軸まわりに30度回転
			object3ds[i].rotation = { 0.0f,0.0f,XMConvertToRadians(30.0f) };

			//親オブジェクトに対してZ方向-8.0ずらす
			object3ds[i].position = { 0.0f,0.0f,-8.0f };
		}
	}

	////射影変換行列の計算
	matProjection =
		XMMatrixPerspectiveFovLH(
			XMConvertToRadians(45.0f),//上下画角45度
			(float)WinApp::window_width / WinApp::window_height,//アスペクト比(画面横幅/画面縦幅)
			0.1f, 1000.0f//前端,奥端
		);
	////ビュー変換行列を計算
	XMFLOAT3 eye(0, 0, -100);	//始点座標
	XMFLOAT3 target(0, 0, 0);	//注視点座標
	XMFLOAT3 up(0, 1, 0);		//上方向ベクトル
	matview = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

#pragma region 画像データ
#pragma region リソースデータ作成

#pragma endregion
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	//WICテクスチャのロード
	result = LoadFromWICFile(
		L"Resource/test.png",
		WIC_FLAGS_NONE,
		&metadata, scratchImg
	);
	ScratchImage mipChain{};
	//ミニマップ生成
	result = GenerateMipMaps(
		scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(),
		TEX_FILTER_DEFAULT, 0, mipChain);
	if (SUCCEEDED(result)) {
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}
	//読み込んだディヒューズテクスチャをSRGBとして使う
	metadata.format = MakeSRGB(metadata.format);
	//ヒープ設定
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	textureHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	//リソース設定
	D3D12_RESOURCE_DESC textureResourceDesc{};
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc.Format = metadata.format;
	textureResourceDesc.Width = metadata.width; //幅
	textureResourceDesc.Height = metadata.height; //高さ
	textureResourceDesc.DepthOrArraySize = (UINT)metadata.arraySize;
	textureResourceDesc.MipLevels = (UINT)metadata.mipLevels;
	textureResourceDesc.SampleDesc.Count = 1;

	//テクスチャバッファの生成
	ID3D12Resource* texBuff = nullptr;
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&textureHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&textureResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&texBuff));

	//全ミニマップについて
	for (size_t i = 0; i < metadata.mipLevels; i++) {
		//ミニマップレベルを指定してイメージを取得
		const Image* img = scratchImg.GetImage(i, 0, 0);
		//テクスチャバッファにデータ転送
		result = texBuff->WriteToSubresource(
			(UINT)i,
			nullptr,				//全領域へコピー
			img->pixels,			//元データアドレス
			(UINT)img->rowPitch,	//1ラインサイズ
			(UINT)img->slicePitch	//1枚サイズ
		);
		assert(SUCCEEDED(result));
	}

	//SRVの最大個数
	const size_t kMaxSRVCount = 2056;

	//デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc{};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダーから見えるように
	srvHeapDesc.NumDescriptors = kMaxSRVCount;

	//設定を元にSRV用デスクリプタヒープを生成

	result = dxCommon->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvHeap));
	assert(SUCCEEDED(result));

	//SRVヒープの先頭ハンドル取得
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();

	//シェーダリソースビュー
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; //設定構造体
	srvDesc.Format = resDesc.Format; //RGBA float
	srvDesc.Shader4ComponentMapping =
		D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; //2Dテクスチャ
	srvDesc.Texture2D.MipLevels = resDesc.MipLevels;

	//ハンドルの指す位置にシェーダーリソースビュー作成
	dxCommon->GetDevice()->CreateShaderResourceView(texBuff, &srvDesc, srvHandle);


#pragma endregion


	//値を書き込むと自動に転送される
	constMapMaterial->color = XMFLOAT4(1, 1, 1, 1);//色
}

void Sprite::Update()
{
	UpdateObject3d(&object3ds[0], matview, matProjection);
}

void Sprite::Draw()
{
	// パイプラインステートとルートシグネチャの設定コマンド
	dxCommon->GetCommandList()->SetPipelineState(spritecommon->GetPipelineState());
	dxCommon->GetCommandList()->SetGraphicsRootSignature(spritecommon->GetRootSignature());
	// プリミティブ形状の設定コマンド
	dxCommon->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト
	// 頂点バッファビューの設定コマンド
	dxCommon->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);
	//定数バッファビュー(CBV)の設定コマンド
	dxCommon->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetGPUVirtualAddress());

	//SRVヒープの設定コマンド
	dxCommon->GetCommandList()->SetDescriptorHeaps(1, &srvHeap);
	//SRVヒープの先頭ハンドルを取得(SRVを指定しているはず)
	D3D12_GPU_DESCRIPTOR_HANDLE srvGpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();
	//SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
	dxCommon->GetCommandList()->SetGraphicsRootDescriptorTable(1, srvGpuHandle);
	//インデックスバッファビューの設定コマンド
	dxCommon->GetCommandList()->IASetIndexBuffer(&ibView);
	//全オブジェクトについての処理
	DrawObject3d(&object3ds[0], dxCommon->GetCommandList(), vbView, ibView, _countof(indices));
}
