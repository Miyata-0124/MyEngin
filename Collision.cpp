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
    //球1の座標
    XMVECTOR vector1 = sphere.center;
    //球2の座標
    XMVECTOR vector2 = sphere2.center;

    //球1の半径
    float radius1 = sphere.radius;
    //球2の半径
    float radius2 = sphere2.radius;

    float a = vector1.m128_f32[0] - vector2.m128_f32[0];
    float b = vector1.m128_f32[1] - vector2.m128_f32[1];
    float c = vector1.m128_f32[2] - vector2.m128_f32[2];

    double d = sqrt((a * a) + (b * b) + (c * c));

    if (d > radius1+radius2)return false;
    else return true;
}

bool Collision::CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance, DirectX::XMVECTOR* inter)
{
    const float epsilon = 1.0e-5f;//誤差吸収用の微小な値
    //面法線とレイの方向ベクトル
    float d1 = XMVector3Dot(plane.normal, ray.dir).m128_f32[0];
    //裏面に当たらない
    if (d1 > -epsilon) { return false; }
    //始点と原点の距離(平面の法線ベクトル)
    //面法線とレイの始点座標(位置ベクトル)の内積
    float d2 = XMVector3Dot(plane.normal, ray.start).m128_f32[0];
    //始点と平面の距離(平面の法線方向)
    float dist = d2 - plane.distance;
    //始点と平面の距離(レイ方向)
    float t = dist / -d1;
    //交点が始点より後ろにあるためハズレ
    if (t < 0)return false;
    //距離
    if (distance) { *distance = t; }
    //交点の計算
    if (inter) { *inter = ray.start + t * ray.dir; }

    return true;
}
