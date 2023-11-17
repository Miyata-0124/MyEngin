#pragma once
#include "header/3D/Object3D.h"
#include "header/Engin/Input.h"

class MoveGate : public Object3d
{
public:
	/// <summary>
	/// オブジェクト生成
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static MoveGate* Create(Model* model = nullptr);

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

	/// <summary>
	/// キー情報セット
	/// </summary>
	/// <param name="input">キー情報</param>
	/// <returns></returns>
	Input* SetInput(Input* input_) { return this->input = input_; }

	bool GetMapMove() { return isMapMove; }
	void SetMapMove(bool isMapMove_) { isMapMove = isMapMove_; }
private:
	Input* input = nullptr;
private:
	//半径
	XMFLOAT2 radius = { 1.0f,1.0f };

	//フラグ
	bool isMapMove = false;
};

