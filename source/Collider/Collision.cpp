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
    float Xmax = box.center.m128_f32[0] + box.radius;
    float Ymax = box.center.m128_f32[1] + box.radius;
    DirectX::XMFLOAT2 Pmax = { Xmax,Ymax };
    //最小点
    float Xmin = box.center.m128_f32[0] - box.radius;
    float Ymin = box.center.m128_f32[1] - box.radius;
    DirectX::XMFLOAT2 Pmin = { Xmin,Ymin };

    DirectX::XMFLOAT2 SpherePos = { sphere.center.m128_f32[0],sphere.center.m128_f32[1] };

    if (SpherePos.y + sphere.radius > Pmin.y && SpherePos.y - sphere.radius < Pmax.y)
    {
        if (SpherePos.x + sphere.radius > Pmin.x && SpherePos.x - sphere.radius < Pmax.x)
        {
            return true;
        }
    }

    return false;
}

float Collision::LenOBBToPoint(OBB& obb, DirectX::XMVECTOR& p)
{
    DirectX::XMVECTOR Vec = { 0,0,0 }; //長さを求めるベクトル
    //各軸についてはみ出た部分のベクトル算出
    for (int i = 0; i < 3; i++)
    {
        float L = obb.fLength[i];
        //L=0計算しない
        if (L <= 0) {
            continue;
        }
        DirectX::XMVECTOR p_pos = (p - obb.pos);
        DirectX::XMVECTOR s = XMVector3Dot(p_pos, obb.normalDir[i]) / L;

    }
    return 0.0f;
}

bool Collision::CheckOBB2Sphere(const OBB& obb, const Sphere& sphere, DirectX::XMVECTOR* inter, DirectX::XMVECTOR* reject)
{
   
    return true;
}

//OBBと点の最短距離算出関数
//float Collision::LenOBBToPoint(OBB& obb, Vector3& p)
//{
//    //Vector3 Vec(0,0,0);   // 長さを求めるベクトル
//
//    //// 各軸についてはみ出た部分のベクトルを算出
//    //for (int i = 0; i < 3; i++)
//    //{
//    //    float L = obb.fLength[i];
//    //    // L=0は計算無し
//    //    if (L <= 0) {
//    //        continue;
//    //    }
//    //    float s = Vector3(p - obb.Pos).dot(obb.NormaDirect[i]) / L;
//
//    //    // sの値から、はみ出した部分があったならそのベクトルを加算
//    //    s = (float)fabs(s);
//    //    if (s > 1) {
//    //        Vec += (1 - s) * L * obb.NormaDirect[i];   // はみ出した部分のベクトル算出
//    //    }
//    //}
//    ////result = Vec.length();
//
//    //return Vec.length();   // 長さを出力
//}
//
//bool Collision::CheckOBB2Sphere(const OBB& obb, const Sphere& sphere,Vector3* inter, Vector3* reject)
//{
//    //float length; ///
//    //DirectX::XMVECTOR rejectLen;
//    //Vector3 inter_;
//    //OBB obb_ = obb;
//    //Vector3 spherePos = sphere.center;
//    //Vector3 obbPos = obb_.Pos;
//    //Vector3 rejeVec;
//
//    //rejeVec = sphere.center - obbPos;
//    ////正規化
//    //rejeVec.nomalize();
//
//    //length = LenOBBToPoint(obb_, spherePos);
//
//    //inter_ = obb_.Pos + (rejeVec * (length - sphere.radius));
//    //if ((float)fabs(length) > sphere.radius) {
//    //    rejectLen.m128_f32[0] = length;
//
//    //    return false;
//    //}
//
//    ////疑似交点
//    //if (inter)
//    //{
//    //    //平面上の最近接点を疑似交点とする
//    //    *inter = obb_.Pos + (rejeVec * length);
//    //}
//    //return true;
//}