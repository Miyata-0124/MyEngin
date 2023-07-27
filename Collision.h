#pragma once
#include "CollisionPrimitive.h"

class Collision
{
public:
	/// <summary>
	/// 球と平面
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="plane">平面</param>
	/// <param name="inter">交点</param>
	/// <returns></returns>
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, DirectX::XMVECTOR* inter = nullptr);
	/// <summary>
	/// 球と球
	/// </summary>
	/// <param name="sphere">球1</param>
	/// <param name="sphere2">球2</param>
	/// <param name="inter">交点</param>
	/// <returns></returns>
	static bool CheckSphere2Sphere(const Sphere& sphere, const Sphere& sphere2, DirectX::XMVECTOR* inter);
	/// <summary>
	/// レイと平面
	/// </summary>
	/// <param name="ray">レイ</param>
	/// <param name="plane">平面</param>
	/// <param name="distance">距離</param>
	/// <param name="inter">交点</param>
	/// <returns>交差しているか</returns>
	static bool CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);
	/// <summary>
	/// 四角と球
	/// </summary>
	/// <param name="box">四角</param>
	/// <param name="sphere">球</param>
	/// <param name="inter">交点</param>
	/// <returns>項さしているか</returns>
	static bool CheckBox2Sphere(const Box& box, const Sphere& sphere, DirectX::XMVECTOR* inter);
};

