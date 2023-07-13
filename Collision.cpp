#include "Collision.h"

using namespace DirectX;

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane, DirectX::XMVECTOR* inter)
{
    //���W�_�̌��_���狅�̒��S�_���W
    XMVECTOR distV = XMVector3Dot(sphere.center, plane.normal);
    //���ʂƋ��̒��S�Ƃ̋���
    float dist = distV.m128_f32[0] - plane.distance;
    //�����̐�Βl�����a���傫����΃n�Y��
    if (fabsf(dist) > sphere.radius)return false;

    //�^����_���쐬
    if (inter) {
        //���ʏ�̍ŋߐړ_���^���ɐݒ�
        *inter = -dist * plane.normal + sphere.center;
    }
    return true;
}

bool Collision::CheckSphere2Sphere(const Sphere& sphere, const Sphere& sphere2, DirectX::XMVECTOR* inter)
{
    float sideA = sphere2.center.m128_f32[0] - sphere.center.m128_f32[0]; //X
    float sideB = sphere2.center.m128_f32[1] - sphere.center.m128_f32[1]; //Y
    float sideC = sphere2.center.m128_f32[2] - sphere.center.m128_f32[2]; //Z
    float sideD = sphere.radius + sphere2.radius;                         //R

    float sideX = (sideA * sideA);
    float sideY = (sideB * sideB);
    float sideZ = (sideC * sideC);
    float sphereDist = sideX + sideY + sideZ;
    float Radius2 = (sideD * sideD);
    //���������a�����ł�����΃n�Y��
    if (fabsf(sphereDist) >= Radius2)return false;
    else return true;
}