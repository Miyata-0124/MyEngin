#include "Collision.h"

using namespace DirectX;

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane, DirectX::XMVECTOR* inter)
{
    //座標点の原点から球の中心点座標
    XMVECTOR distV = XMVector3Dot(sphere.center, plane.normal);
    //平面と球の中心との距離
    float dist = distV.m128_f32[0] - plane.distance;
    //距離の絶対値が半径より大きければハズレ
    if (fabsf(dist) > sphere.radius)return false;

    //疑似交点を作成
    if (inter) {
        //平面上の最近接点を疑似に設定
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
    //距離が半径よりもでかければハズレ
    if (fabsf(sphereDist) >= Radius2)return false;
    else return true;
}