#include "PlaneCollider.h"

using namespace DirectX;
void PlaneCollider::Update()
{
	//���[���h�s�񂩂���W���o
	const XMMATRIX& matWorld = object3d->GetMatWorld();

	//���̃����o�ϐ����X�V
	Sphere::center = matWorld.r[3] + offset;
	Sphere::radius = distance;
}