#include "PlaneCollider.h"

using namespace DirectX;
void PlaneCollider::Update()
{
	//���[���h�s�񂩂���W���o
	const XMMATRIX& matWorld = object3d->GetMatWorld();

	//���ʂ̃����o�ϐ����X�V
	//�@���x�N�g��
	Plane::normal = matWorld.r[3] + offset;
	//���_����̋���()
	Plane::distance = distance;
}