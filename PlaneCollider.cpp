#include "PlaneCollider.h"

using namespace DirectX;
void PlaneCollider::Update()
{
	//���[���h�s�񂩂���W���o
	const Matrix4& matWorld = object3d->GetMatWorld();

	//���ʂ̃����o�ϐ����X�V
	//�@���x�N�g��
	Plane::normal = { 0,1,0 };
	//���_����̋���()
	Plane::distance = distance;
}