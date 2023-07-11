#pragma once
#include "Object3D.h"
#include "Input.h"

enum class Posture
{
	Upright,
	Croching
};

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

	/// <summary>
	/// キー情報セット
	/// </summary>
	/// <param name="input">キー情報</param>
	/// <returns></returns>
	Input* SetInput(Input* input) { return this->input = input; }
private:
	//左右移動
	void Move();
	//ジャンプ
	void Jamp();
	//姿勢変更
	void ChangePosture();
	//重力
	void Gravity();
private:
	Input* input = nullptr;
	Posture posture = Posture::Upright;
private:
	//重力加算量
	float yadd = 0.0f;
	//半径
	float radius = 0.6f;
	//移動速度
	float moveSpeed = 0.4f;

	//フラグ,タイマー
	//ジャンプフラグ
	bool isJamp = false;
};

