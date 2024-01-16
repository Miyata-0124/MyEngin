#include "header/Collider/Collision.h"

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
//球どうしの判定
bool Collision::CheckSphere2Sphere(const Sphere& sphere, const Sphere& sphere2)
{
    //x
    float x = sphere.center.m128_f32[0] - sphere2.center.m128_f32[0];
    //y
    float y = sphere.center.m128_f32[1] - sphere2.center.m128_f32[1];
    //z
    float z = sphere.center.m128_f32[2] - sphere2.center.m128_f32[2];
    //球どうしの距離
    double d = sqrt((x * x) + (y * y) + (z * z));
    //距離が半径を足したものより小さい(半径の中にいる)ならアタリ
    if (d <= sphere.radius + sphere2.radius)
    {
        return true;
    }
    //それ以外ではハズレとして返す
    return false;
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

bool Collision::CheckSphere2Box2D(const Sphere& sphere, const Box& box)
{

    //最大点
    float Xmax = box.center.m128_f32[0] + box.radius.x;
    float Ymax = box.center.m128_f32[1] + box.radius.y;
    DirectX::XMFLOAT2 Pmax = { Xmax,Ymax };
    //最小点
    float Xmin = box.center.m128_f32[0] - box.radius.x;
    float Ymin = box.center.m128_f32[1] - box.radius.y;
    DirectX::XMFLOAT2 Pmin = { Xmin,Ymin };
    //プレイヤーの座標
    DirectX::XMFLOAT2 SpherePos = { sphere.center.m128_f32[0],sphere.center.m128_f32[1] };

    //もしプレイヤーの座標と2DBoxの2頂点の座標で判定を取る
    if (SpherePos.y > Pmin.y && SpherePos.y < Pmax.y)
    {
        if (SpherePos.x > Pmin.x && SpherePos.x < Pmax.x)
        {
            return true;
        }
    }

    return false;
}