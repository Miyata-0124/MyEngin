#pragma once
#include "CollisionPrimitive.h"

#include "Math/Vector3.h"

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
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, Vector3* inter = nullptr);
	/// <summary>
	/// 球と球
	/// </summary>
	/// <param name="sphere">球1</param>
	/// <param name="sphere2">球2</param>
	/// <param name="inter">交点</param>
	/// <returns></returns>
	static bool CheckSphere2Sphere(const Sphere& sphere, const Sphere& sphere2);
	/// <summary>
	/// レイと平面
	/// </summary>
	/// <param name="ray">レイ</param>
	/// <param name="plane">平面</param>
	/// <param name="distance">距離</param>
	/// <param name="inter">交点</param>
	/// <returns>交差しているか</returns>
	static bool CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance = nullptr, Vector3* inter = nullptr);

	//static float LenOBBToPoint(OBB & obb,Vector3 & p);
	//static bool CheckOBB2Sphere(const OBB& obb, const Sphere& sphere, Vector3* inter, Vector3* reject);
};

