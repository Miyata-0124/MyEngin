#include "SphereCollider.h"

void SphereCollider::Update()
{
	//ワールド行列から座標抽出
	const Matrix4& matWorld = object3d->GetMatWorld();

	//球のメンバ変数を更新
	Sphere::center = {
		matWorld.m[3][0] + offset.x ,
		matWorld.m[3][1] + offset.y ,
		matWorld.m[3][2] + offset.z
	};
	Sphere::radius = radius;
}
