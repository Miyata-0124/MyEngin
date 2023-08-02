#pragma once
#include<Windows.h>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<cassert>
#include<DirectXMath.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include "DirectXTex/d3dx12.h"
#include <nlohmann/json.hpp>
#include "Model.h"
#include "Object3D.h"

//データ格納用
struct LevelData
{
	struct ObjectData
	{
		// ファイル名
		std::string fileName;
		// 平行移動
		DirectX::XMVECTOR position;
		// 回転角
		DirectX::XMVECTOR rotation;
		// スケーリング
		DirectX::XMVECTOR scaling;
		//コライダー
		// コライダー名
		std::string collName;
		// 中心
		DirectX::XMVECTOR center;
		// サイズ
		DirectX::XMVECTOR size;
	};

	//オブジェクト配列
	std::vector<ObjectData> objects;
};

class JsonLoader
{
public:
	//json読み込み
	static LevelData* LoadFlomJSONInternal(const std::string& modelname);
private:

};

