#include "header/Collider/Collision.h"

using namespace DirectX;

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane, DirectX::XMVECTOR* inter)
{
    //���W�_�̌��_���狅�̒��S�_���W
    XMVECTOR distV = XMVector3Dot(sphere.center, plane.normal);
    //���ʂƋ��̒��S�Ƃ̋���
    float dist = distV.m128_f32[0] - plane.distance;
    //�����̐�Βl�����a���傫����΃n�Y��
    if (fabsf(dist) > sphere.radius)return false;

    //�^����_��쐬
    if (inter) {
        //���ʏ�̍ŋߐړ_��^���ɐݒ�
        *inter = -dist * plane.normal + sphere.center;
    }
    return true;
}
//���ǂ����̔���
bool Collision::CheckSphere2Sphere(const Sphere& sphere, const Sphere& sphere2)
{
    //x
    float x = sphere.center.m128_f32[0] - sphere2.center.m128_f32[0];
    //y
    float y = sphere.center.m128_f32[1] - sphere2.center.m128_f32[1];
    //z
    float z = sphere.center.m128_f32[2] - sphere2.center.m128_f32[2];
    //���ǂ����̋���
    double d = sqrt((x * x) + (y * y) + (z * z));
    //���������a�𑫂�����̂�菬����(���a�̒��ɂ���)�Ȃ�A�^��
    if (d <= sphere.radius + sphere2.radius)
    {
        return true;
    }
    //����ȊO�ł̓n�Y���Ƃ��ĕԂ�
    return false;
}

bool Collision::CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance, DirectX::XMVECTOR* inter)
{
    const float epsilon = 1.0e-5f;//�덷�z���p�̔����Ȓl
    //�ʖ@���ƃ��C�̕����x�N�g��
    float d1 = XMVector3Dot(plane.normal, ray.dir).m128_f32[0];
    //���ʂɓ�����Ȃ�
    if (d1 > -epsilon) { return false; }
    //�n�_�ƌ��_�̋���(���ʂ̖@���x�N�g��)
    //�ʖ@���ƃ��C�̎n�_���W(�ʒu�x�N�g��)�̓��
    float d2 = XMVector3Dot(plane.normal, ray.start).m128_f32[0];
    //�n�_�ƕ��ʂ̋���(���ʂ̖@������)
    float dist = d2 - plane.distance;
    //�n�_�ƕ��ʂ̋���(���C����)
    float t = dist / -d1;
    //��_���n�_�����ɂ��邽�߃n�Y��
    if (t < 0)return false;
    //����
    if (distance) { *distance = t; }
    //��_�̌v�Z
    if (inter) { *inter = ray.start + t * ray.dir; }

    return true;
}

bool Collision::CheckSphere2Box2D(const Sphere& sphere, const Box& box)
{
    XMFLOAT2 sphere_ = { sphere.center.m128_f32[0] , sphere.center.m128_f32[1] };
    XMFLOAT4 box_ = {
        box.center.m128_f32[0] + box.radius , //x x1
        box.center.m128_f32[0] - box.radius , //y x2
        box.center.m128_f32[1] + box.radius , //z y1
        box.center.m128_f32[1] - box.radius   //w y2
    };

    //x,y��2���̂�

    // X ����X��box��X2�_�̊�
    if (sphere_.x < box_.x && sphere_.x > box_.y)
    {
        // Y ����Y��box��Y�̊�
        if (sphere_.y<box_.z && sphere_.y>box_.w)
        {
            //�Ȃ�q�b�g
            return true;
        }
    }
    //����ȊO�n�Y��
    return false;
}

//float Collision::LenOBBToPoint(OBB& obb, DirectX::XMVECTOR& p)
//{
//    DirectX::XMVECTOR Vec = { 0,0,0 }; //��������߂�x�N�g��
//    //�e���ɂ��Ă͂ݏo�������̃x�N�g���Z�o
//    for (int i = 0; i < 3; i++)
//    {
//        float L = obb.fLength[i];
//        //L=0�v�Z���Ȃ�
//        if (L <= 0) {
//            continue;
//        }
//        DirectX::XMVECTOR p_pos = (p - obb.pos);
//        DirectX::XMVECTOR s = XMVector3Dot(p_pos, obb.normalDir[i]) / L;
//
//    }
//    return 0.0f;
//}

//bool Collision::CheckOBB2Sphere(const OBB& obb, const Sphere& sphere, DirectX::XMVECTOR* inter, DirectX::XMVECTOR* reject)
//{
//   
//    return true;
//}

//OBB�Ɠ_�̍ŒZ�����Z�o�֐�
//float Collision::LenOBBToPoint(OBB& obb, Vector3& p)
//{
//    //Vector3 Vec(0,0,0);   // ��������߂�x�N�g��
//
//    //// �e���ɂ��Ă͂ݏo�������̃x�N�g����Z�o
//    //for (int i = 0; i < 3; i++)
//    //{
//    //    float L = obb.fLength[i];
//    //    // L=0�͌v�Z����
//    //    if (L <= 0) {
//    //        continue;
//    //    }
//    //    float s = Vector3(p - obb.Pos).dot(obb.NormaDirect[i]) / L;
//
//    //    // s�̒l����A�͂ݏo�����������������Ȃ炻�̃x�N�g������Z
//    //    s = (float)fabs(s);
//    //    if (s > 1) {
//    //        Vec += (1 - s) * L * obb.NormaDirect[i];   // �͂ݏo���������̃x�N�g���Z�o
//    //    }
//    //}
//    ////result = Vec.length();
//
//    //return Vec.length();   // ������o��
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
//    ////���K��
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
//    ////�^����_
//    //if (inter)
//    //{
//    //    //���ʏ�̍ŋߐړ_��^����_�Ƃ���
//    //    *inter = obb_.Pos + (rejeVec * length);
//    //}
//    //return true;
//}