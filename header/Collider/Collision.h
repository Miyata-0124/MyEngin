/**
 * @file Collision.h
 * @brief �e��������ꂼ����ׂ̋@�\
 * @author �~���^_�R�E�L
 * @date 2023/07/25
 */

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
	static bool CheckSphere2Sphere(const Sphere& sphere, const Sphere& sphere2);
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
	/// <summary>
	/// 2D�l�p*2
	/// </summary>
	/// <param name="box"></param>
	/// <param name="box"></param>
	/// <returns></returns>
	static bool CheckBox2DBox2D(const Box& box1, const Box& box2);
};
	

