#include "SphereCollider.h"

void SphereCollider::Update()
{
	//���[���h�s�񂩂���W���o
	const Matrix4& matWorld = object3d->GetMatWorld();

	//���̃����o�ϐ����X�V
	Sphere::center = {
		matWorld.m[3][0] + offset.x ,
		matWorld.m[3][1] + offset.y ,
		matWorld.m[3][2] + offset.z
	};
	Sphere::radius = radius;
}
