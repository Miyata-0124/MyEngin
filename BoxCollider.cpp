#include "BoxCollider.h"

void BoxCollider::Update()
{
	//ワールド行列から座標抽出
	const XMMATRIX& matWorld = object3d->GetMatWorld();

	Box::center = matWorld.r[3] + center;
	Box::point[0] = center.m128_f32[0] - radius;
	Box::point[1] = center.m128_f32[0] + radius;
	Box::point[2] = center.m128_f32[1] - radius;
	Box::point[3] = center.m128_f32[1] + radius;
}
