#pragma once
#include "CollisionPrimitive.h"

class Collision
{
public:
	/// <summary>
	/// ‹…‚Æ•½–Ê
	/// </summary>
	/// <param name="sphere">‹…</param>
	/// <param name="plane">•½–Ê</param>
	/// <param name="inter">Œð“_</param>
	/// <returns></returns>
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, DirectX::XMVECTOR* inter = nullptr);
};

