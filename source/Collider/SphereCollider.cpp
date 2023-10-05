#include "header/Collider/SphereCollider.h"

using namespace DirectX;
void SphereCollider::Update()
{
	//ワールド行列から座標抽出
	const XMMATRIX& matWorld = object3d->GetMatWorld();

	//球のメンバ変数を更新
	Sphere::center = matWorld.r[3] + offset;
	Sphere::radius = radius;
}