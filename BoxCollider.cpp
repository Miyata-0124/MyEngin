#include "BoxCollider.h"

void BoxCollider::Update()
{
	//���[���h�s�񂩂���W���o
	const XMMATRIX& matWorld = object3d->GetMatWorld();

	Box::center = { 0,0,0,1 };
	Box::radius = radius;
}
