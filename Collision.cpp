#include "Collision.h"

using namespace DirectX;

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane, Vector3* inter)
{
    //座標点の原点から球の中心点座標
    float distV = sphere.center.dot(plane.normal);
    //平面と球の中心との距離
    float dist = distV - plane.distance;
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
    float x = sphere.center.x - sphere2.center.x;
    //y
    float y = sphere.center.y - sphere2.center.y;
    //z
    float z = sphere.center.z - sphere2.center.z;
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
//レイと平面
bool Collision::CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance, Vector3* inter)
{
    const float epsilon = 1.0e-5f;//誤差吸収用の微小な値
    //面法線とレイの方向ベクトル
    float d1 = plane.normal.dot(ray.dir);
    //裏面に当たらない
    if (d1 > -epsilon) { return false; }
    //始点と原点の距離(平面の法線ベクトル)
    //面法線とレイの始点座標(位置ベクトル)の内積
    float d2 = plane.normal.dot(ray.start);
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