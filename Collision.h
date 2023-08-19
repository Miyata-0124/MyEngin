#pragma once
#include "CollisionPrimitive.h"

#include "Math/Vector3.h"

class Collision
{
public:
	/// <summary>
	/// ���ƕ���
	/// </summary>
	/// <param name="sphere">��</param>
	/// <param name="plane">����</param>
	/// <param name="inter">��_</param>
	/// <returns></returns>
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, Vector3* inter = nullptr);
	/// <summary>
	/// ���Ƌ�
	/// </summary>
	/// <param name="sphere">��1</param>
	/// <param name="sphere2">��2</param>
	/// <param name="inter">��_</param>
	/// <returns></returns>
	static bool CheckSphere2Sphere(const Sphere& sphere, const Sphere& sphere2);
	/// <summary>
	/// ���C�ƕ���
	/// </summary>
	/// <param name="ray">���C</param>
	/// <param name="plane">����</param>
	/// <param name="distance">����</param>
	/// <param name="inter">��_</param>
	/// <returns>�������Ă��邩</returns>
	static bool CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance = nullptr, Vector3* inter = nullptr);

	//static float LenOBBToPoint(OBB & obb,Vector3 & p);
	//static bool CheckOBB2Sphere(const OBB& obb, const Sphere& sphere, Vector3* inter, Vector3* reject);
};

