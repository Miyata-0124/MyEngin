#include "BoxCollider.h"

using namespace DirectX;
void BoxCollider::Update()
{
	//���[���h�s�񂩂���W���o
	const XMMATRIX& matWorld = object3d->GetMatWorld();

	Box::center = matWorld.r[3] + center;
	Box::radius = radius;
}
