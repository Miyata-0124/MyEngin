#pragma once
#include <DirectXMath.h>
#include "Matrix4.h"
#include "Vector4.h"

using namespace DirectX;

class Convert
{

public:
	static Matrix4 ConvertXMMATtoMat4(XMMATRIX XMMat);
	static XMMATRIX ConvertMat4toXMMAT(Matrix4 Mat4);

	static Vector3 ConvertXMFlo3toVec3(XMFLOAT3 XMFlo3);
	static XMFLOAT3 ConvertVec3toXMFlo3(Vector3 vec3);

	static Vector4 XMVECToVec4(XMVECTOR XMVEC);
	static XMVECTOR Vec4ToXMVEC(Vector4 Vec4);
private:

};
