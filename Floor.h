#pragma once
#include "Object3D.h"
#include "Model.h"

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
	float distance = -7.0f;
	//半径
	float radius = 0.5f;
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

