#include "BoxCollider.h"

void BoxCollider::Update()
{
	//ワールド行列から座標抽出
	const XMMATRIX& matWorld = object3d->GetMatWorld();

	Box::center = { 0,0,0,1 };
	Box::radius = radius;
}
