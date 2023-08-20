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

struct OBB
{
//public:
//	Vector3 Pos;              
//	Vector3 NormaDirect[3];   
//	float fLength[3];         
//
//	OBBPlane plane[6];

	DirectX::XMVECTOR pos = { 0,0,0,0 };	// 位置
	DirectX::XMVECTOR normalDir[3];			// 方向ベクトル
	float fLength[3];					    // 各軸方向の長さ
};
struct OBBPlane {
	////法線ベクトル
	//Vector3 normal = { 0,1,0 };
	////原点(0,0,0)からの距離
	//float distance = 0.0f;

	//Vector3 vertex[4];
	//Vector3 pos = { 0,0,0 };
	DirectX::XMVECTOR normal = { 0,1,0,0 };
	float distance = 0.0f;
	DirectX::XMVECTOR vertex[4];
	DirectX::XMVECTOR pos = { 0,0,0,0 };
};