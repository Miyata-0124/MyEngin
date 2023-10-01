#pragma once
#include "CollisionPrimitive.h"

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
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, DirectX::XMVECTOR* inter = nullptr);
	/// <summary>
	/// ���Ƌ�
	/// </summary>
	/// <param name="sphere">��1</param>
	/// <param name="sphere2">��2</param>
	/// <param name="inter">��_</param>
	/// <returns></returns>
	static bool CheckSphere2Sphere(const Sphere& sphere, const Sphere& sphere2, DirectX::XMVECTOR* inter);
	/// <summary>
	/// ���C�ƕ���
	/// </summary>
	/// <param name="ray">���C</param>
	/// <param name="plane">����</param>
	/// <param name="distance">����</param>
	/// <param name="inter">��_</param>
	/// <returns>�������Ă��邩</returns>
	static bool CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);
	/// <summary>
	/// ���Ǝl�p
	/// </summary>
	/// <param name="sphere"></param>
	/// <param name="box"></param>
	/// <returns></returns>
	static bool CheckSphere2Box2D(const Sphere& sphere, const Box& box);

	static float LenOBBToPoint(OBB& obb, DirectX::XMVECTOR& p);
	static bool CheckOBB2Sphere(const OBB& obb, const Sphere& sphere, DirectX::XMVECTOR* inter, DirectX::XMVECTOR* reject);
};
	

