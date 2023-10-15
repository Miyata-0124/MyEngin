/**
 * @file BackGround.h
 * @brief 天球の機能
 * @author ミヤタ_コウキ
 * @date 2023/08/01
 */

#pragma once
#include "header/3D/Object3D.h"

class BackGround : public Object3d
{
public:
	/// <summary>
	/// オブジェクト生成
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static BackGround* Create(Model* model = nullptr);

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
};

