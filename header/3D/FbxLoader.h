#pragma once

#include "fbxsdk.h"

#include <d3d12.h>
#include <d3dx12.h>
#include<cassert>
#include <string>

#include "FbxModel.h"

class FbxLoader
{
private: //エイリアス
	//std省略
	using string = std::string;
public: //定数
	//モデル格納パス
	static const string baseDirectory;
	static const string defaultTextureFileName;
public:
	static void ConvertMatrixFromFbx(DirectX::XMMATRIX* dst, const FbxAMatrix& src);
public:
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FbxLoader* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device"></param>
	void Initialize(ID3D12Device* device_);

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();

	FbxModel* LoadModelFromFile(const string& modelName);

	/// <summary>
	/// ノード構成を解析
	/// </summary>
	/// <param name="model"></param>
	/// <param name="fbxNode"></param>
	void ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode, Node* parent = nullptr);

	/// <summary>
	/// メッシュ読み取り
	/// </summary>
	/// <param name="model"></param>
	/// <param name="fbxNode"></param>
	void ParseMesh(FbxModel* model, FbxNode* fbxNode);
	//頂点座標読み取り
	void ParseMeshVertices(FbxModel* model, FbxMesh* fbxMesh);
	//面情報読み取り
	void ParseMeshFaces(FbxModel* model, FbxMesh* fbxMesh);
	//マテリアル読み取り
	void ParseMaterial(FbxModel* model, FbxNode* fbxNode);
	//テクスチャ読み取り
	void LoadTexture(FbxModel* model, const std::string& fullpath);
	//スキニング情報の読み取り
	void ParseSkin(FbxModel* model, FbxMesh* fbxMesh);
private:
	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader& obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader& obj) = delete;

	//ID3D12デバイス
	ID3D12Device* device = nullptr;
	//FBXマネージャー
	FbxManager* fbxManager = nullptr;
	//FBXインポーター
	FbxImporter* fbxImporter = nullptr;

	std::string ExtractFileName(const std::string& path);


};