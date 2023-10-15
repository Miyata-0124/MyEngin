/**
 * @file FbxObject3D.h
 * @brief FBXモデルを使用するオブジェクトの機能(アニメーションなども追加出来る)
 * @author ミヤタ_コウキ
 * @date 2023/05/31
 */

#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <string>
#include "DirectXTex/include/d3dx12.h"
#include "FbxModel.h"
#include "FbxLoader.h"
//#include "FbxLoader.h"

/// <summary>
/// 3Dオブジェクト
/// </summary>
class FbxObject3d
{
protected: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public: //静的定数
	//ボーンの最大値
	static const int MAX_BONES = 32;

public: //サブクラス
	//定数バッファ用データ構造体 (座標変換行列用)
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;	//ビュープロジェクション行列
		XMMATRIX world;		//ワールド行列
		XMFLOAT3 cameraPos;	//カメラ座標(ワールド座標)
	};

	//定数バッファ用データ構造体(スキニング)
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};

public: // 静的メンバ変数
	static void SetDevice(ID3D12Device* device_) { FbxObject3d::device = device_; }
	/// <summary>
/// 静的初期化
/// </summary>
/// <param name="device">デバイス</param>
/// <param name="window_width">画面幅</param>
/// <param name="window_height">画面高さ</param>
	static void StaticInitialize(ID3D12Device* device, int window_width, int window_height);

	/// <summary>
	/// カメラ初期化
	/// </summary>
	/// <param name="window_width">画面横幅</param>
	/// <param name="window_height">画面縦幅</param>
	static void InitializeCamera(int window_width, int window_height);

	/// <summary>
	/// グラフィックスパイプラインの生成
	/// </summary>
	static void InitializeGraphicsPipeline();


	/// <summary>
	/// ビュー行列を更新
	/// </summary>
	static void UpdateViewMatrix();

	/// <summary>
	/// 視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	static const XMFLOAT3& GetEye() { return eye; }

	/// <summary>
	/// 視点座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	static void SetEye(XMFLOAT3 eye);

	/// <summary>
	/// 注視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	static const XMFLOAT3& GetTarget() { return target; }

	/// <summary>
	/// 注視点座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	static void SetTarget(XMFLOAT3 target);

	/// <summary>
	/// ベクトルによる移動
	/// </summary>
	/// <param name="move">移動量</param>
	static void CameraMoveVector(XMFLOAT3 move);

protected: //メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource>ConstBufferDataTrans;
	//定数バッファ(スキン)
	ComPtr<ID3D12Resource> constBufferSkin;

private:
	//デバイス
	static ID3D12Device* device;
	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	//パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;
	// ビュー行列
	static XMMATRIX matView;
	// 射影行列
	static XMMATRIX matProjection;
	// 視点座標
	static XMFLOAT3 eye;
	// 注視点座標
	static XMFLOAT3 target;
	// 上方向ベクトル
	static XMFLOAT3 up;

protected:
	//ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	//X,Y,Z軸周りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	//ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	//ローカルワールド変換行列
	XMMATRIX matWorld;
	//モデル
	FbxModel* model = nullptr;

	//アニメーション
	//1フレームの時間
	FbxTime frameTime;
	//アニメーション開始時間
	FbxTime startTime;
	//アニメーション終了時間
	FbxTime endTime;
	//現在時間
	FbxTime currentTime;
	//アニメーション再生
	bool isPlay = false;
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void initialize();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="cmdList"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList);
	/// <summary>
	/// モデルセット
	/// </summary>
	/// <param name="model">モデル</param>
	void SetModel(FbxModel* model_) { this->model = model_; }
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(const XMFLOAT3& position_) { this->position = position_; }
	/// <summary>
	/// オブジェクトサイズの設定
	/// </summary>
	/// <param name="size"></param>
	void SetSize(const XMFLOAT3& size) { this->scale = size; }
	/// <summary>
	/// 回転の設定
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotation(const XMFLOAT3& rotation_) { this->rotation = rotation_; }

	/// <summary>
	/// アニメーション開始
	/// </summary>
	void PlayAnimation();
};