#pragma once

#include <DirectXMath.h>

/// <summary>
/// 球
/// </summary>
struct Sphere
{
	//中心点
	DirectX::XMVECTOR center = { 0,0,0,1 };
	//半径
	float radius = 1.0f;
};

/// <summary>
/// 平面
/// </summary>
struct Plane
{
	//法線ベクトル
	DirectX::XMVECTOR normal = { 0,1,0,0 };
	//原点からの距離
	float distance = 0.0f;
};

/// <summary>
/// レイ(半直線)
/// </summary>
struct Ray
{
	//視点座標
	DirectX::XMVECTOR start = { 0,0,0,1 };
	//方向
	DirectX::XMVECTOR dir = { 1,0,0,0 };
};