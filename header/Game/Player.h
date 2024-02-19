/**
 * @file Player.h
 * @brief 操作可能なプレイヤーオブジェクト
 * @author ミヤタ_コウキ
 * @date 2023/06/15
 */

#pragma once
#include "header/3D/Object3D.h"
#include "header/Engin/Input.h"

enum class Posture //姿勢管理
{
	Upright,	//直立
	Croching,	//しゃがみ
	Climing
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
	Input* SetInput(Input* input_) { return this->input = input_; }

	bool SetIsStop(bool isStop_) { return this->isStop = isStop_; }
	/// <summary>
	/// 半径を渡している
	/// </summary>
	/// <returns></returns>
	float GetRadius() { return radius; }
	//座標受け渡し
	XMFLOAT3 GetPosition() { return position; }
	//現在の姿勢受け渡し
	Posture GetPosture() { return posture; }
	//フラグの受け渡し
	bool GetRetention() { return isRetention; }
	bool GetThrow() { return isThrow; }
	bool GetDirection() { return isDirection; }
	//シーン切り替えに使用する情報
	int GetScene() { return sceneNum; }

private:
	//左右移動
	void Move();
	//ジャンプ
	void Jump();
	//ハイジャンプ
	void HiJump();
	//姿勢変更
	void ChangePosture();
	//上り下りの動作
	void Clim(const XMFLOAT3& Rotation);
	//重力
	void Gravity();
	//アイテムに対する行動
	void Retention();
private:
	Input* input = nullptr;
	Posture posture = Posture::Upright;
private:
	//重力加算量
	float yadd = 0.0f;
	//ジャンプ時の反重力
	float antiYadd = -1.5f;
	//半径
	float radius = 2.0f;
	//移動速度
	float moveSpeed = 0.4f;
	bool isMove = true;
	//横にハイジャンプ
	float hiJumpTimer = 5.0f;

	//フラグ,タイマー
	// 向き( false=右 , true=左)
	bool isDirection = false;
	//ジャンプ
	bool isJamp = true;
	//アイテムを保持
	bool isRetention = false;
	//投擲フラグ
	bool isThrow = false;
	//アイテムが刺さっているかの判別
	bool isStop = false;

	int sceneNum = 0;

	//カメラの速度
	float cameraSpeed = 0.0f;
};