#include "BoxCollider.h"

using namespace DirectX;
void BoxCollider::Update()
{
	//ワールド行列から座標抽出
	const XMMATRIX& matWorld = object3d->GetMatWorld();

	Box::center = matWorld.r[3] + center;
	Box::radius = radius;
}
