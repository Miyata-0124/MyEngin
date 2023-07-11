#include "Collision.h"

using namespace DirectX;

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane, DirectX::XMVECTOR* inter)
{
    //座標店の原点から球の中心点座標
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
