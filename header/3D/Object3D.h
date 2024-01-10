/**
 * @file Object3D.h
 * @brief OBJモデルをゲーム内で扱う為の機能
 * @author ミヤタ_コウキ
 * @date 2022/07/20
 */

#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include "DirectXTex/include/d3dx12.h"
#include "Model.h"
#include "header/Collider/CollisionInfo.h"
#include "header/Engin/ViewProjection.h"

class BaseCollider;

enum Identification //属性
{
	IDENT_UNKNOWN = -1,
	IDENT_PLAYER,		//プレイヤー
	IDENT_NEUTRAL,		//中立
	IDENT_ENEMY,		//敵対
	IDENT_FREND,		//友好
	IDENT_ITEM,			//アイテム
	IDENT_GOAL,			//ゴール
	IDENT_GATE,			//イベント
	IDENT_WALL,			//壁
	IDENT_FLOOR,		//床
	IDENT_PIPE,			//パイプ(登れる)
};

/// <summary>
/// 3Dオブジェクト
/// </summary>
class Object3d
{
protected: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
	// 定数バッファ用データ構造体
	struct ConstBufferDataB0
	{
		//XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列
	};

private: // 定数
	static const int division = 50;	// 分割数
	static const float prizmHeight;	// 柱の高さ
	static const int planeCount = division * 2 + division * 2; // 面の数
	static const int vertexCount = planeCount * 3; // 頂点数

public: // 静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	static void StaticInitialize(ID3D12Device* device, ViewProjection* camera_);

	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="cmdList">描画コマンドリスト</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Object3d* Create();

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

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
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

	//カメラ
	static ViewProjection* camera;
private:// 静的メンバ関数
	/// <summary>
	/// カメラ初期化
	/// </summary>
	/// <param name="window_width">画面横幅</param>
	/// <param name="window_height">画面縦幅</param>
	static void InitializeCamera(ViewProjection* camera_);

	/// <summary>
	/// グラフィックパイプライン生成
	/// </summary>
	/// <returns>成否</returns>
	static void InitializeGraphicsPipeline();

	/// <summary>
	/// ビュー行列を更新
	/// </summary>
	static void UpdateViewMatrix();

public: // メンバ関数

	Object3d() = default;

	virtual ~Object3d();

	virtual bool Initialize();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	#pragma warning(suppress: 4100)
	virtual void OnCollider(const CollisionInfo& info) {};

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const XMFLOAT3& GetPosition() const { return position; }

	/// <summary>
	/// サイズの取得
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetScale()const { return scale; }

	/// <summary>
	/// 回転の取得
	/// </summary>
	/// <returns></returns>
	const XMFLOAT3& GetRotation()const { return rotation; }

	const XMFLOAT2& GetRadius()const { return radius; }
	//セッター
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(const XMFLOAT3& position_) { this->position = position_; }
	/// <summary>
	/// オブジェクトサイズの設定
	/// </summary>
	/// <param name="size"></param>
	void SetScale(const XMFLOAT3& scale_) { this->scale = scale_; }
	/// <summary>
	/// 回転角の設定
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotation(const XMFLOAT3& rotation_) { this->rotation = rotation_; }
	/// <summary>
	/// 半径の設定
	/// </summary>
	/// <param name="radius_"></param>
	void SetRadius(const XMFLOAT2& radius_) { this->radius = radius_; }
	/// <summary>
	/// モデルセット
	/// </summary>
	/// <param name="model_"></param>
	void SetModel(Model* model_) { model = model_; }
	/// <summary>
	/// ワールド行列の取得
	/// </summary>
	/// <returns></returns>
	const XMMATRIX& GetMatWorld() { return matWorld; }
	/// <summary>
	/// コライダーのセット
	/// </summary>
	/// <param name="collider"></param>
	void SetCollider(BaseCollider* collider);
	/// <summary>
	/// 識別コード
	/// </summary>
	/// <param name="ident_"></param>
	void SetIdentification(Identification ident_);
	const Identification& GetIdentification() { return ident; }
protected: // メンバ変数
	//ComPtr<ID3D12Resource> constBuff; // 定数バッファ
	ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ
	//ComPtr<ID3D12Resource> constBuffB1; // 定数バッファ
	// 色
	XMFLOAT4 color = { 1,1,1,1 };
	// ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	// ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	//半径
	XMFLOAT2 radius = { 0,0 };	//
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	XMMATRIX matScale, matRot, matTrans;
	// 親オブジェクト
	Object3d* parent = nullptr;
	//モデル
	Model* model = nullptr;

	const char* name = nullptr;
	BaseCollider* collider = nullptr;

	//それぞれが持つ識別コード
	Identification ident = IDENT_UNKNOWN;
};