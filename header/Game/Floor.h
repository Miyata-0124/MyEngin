/**
 * @file Floor.h
 * @brief 世界の底の判定機能
 * @author ミヤタ_コウキ
 * @date 2023/07/09
 */

#pragma once
#include "header/3D/Object3D.h"
#include "header/3D/Model.h"
//最も低い地形クラス

class Floor : public Object3d
{
public:
	/// <summary>
	/// オブジェクト生成
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static Floor* Create(Model* model = nullptr);

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns></returns>
	bool Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// コールバック
	/// </summary>
	/// <param name="info"></param>
	void OnCollider(const CollisionInfo& info)override;
private:
	//原点からの距離
	XMVECTOR distance = { 0,-13.0f,0 };
	//半径
	XMVECTOR radius = { 40.0f, 1.0f,10.0f };
//public:
//	void Initialize(Model* model);
//	void Update();
//	void Draw();
//
//	//Getter,Setter
//	XMFLOAT3 GetPosition() { return position; }
//
//	XMMATRIX GetMatWorld() { return obj3d->GetMatWorld(); }
//private:
//	Object3d* obj3d;
//	//情報(大きさ,回転角,座標)
//	XMFLOAT3 scale;
//	XMFLOAT3 rotation;
//	XMFLOAT3 position;
};

