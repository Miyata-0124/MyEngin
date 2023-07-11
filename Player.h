#pragma once
#include "Object3D.h"
#include "Input.h"

class Player : public Object3d
{
public:
	/// <summary>
	/// オブジェクト生成
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static Player* Create(Model* model = nullptr);

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

	//キー情報をセット
	Input* SetInput(Input* input) { return this->input = input; }
private:
	//左右移動
	void Move();
	//ジャンプ
	void Jamp();
	//重力
	void Gravity();

private:
	Input* input = nullptr;
private:
	float yadd;
	float radius = 0.6f;
};

