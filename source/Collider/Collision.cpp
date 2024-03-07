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

    //�^����_���쐬
    if (inter) {
        //���ʏ�̍ŋߐړ_���^���ɐݒ�
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
    //���������a�𑫂������̂�菬����(���a�̒��ɂ���)�Ȃ�A�^��
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
    //�ʖ@���ƃ��C�̎n�_���W(�ʒu�x�N�g��)�̓���
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

    //�ő�_
    float Xmax = box.center.m128_f32[0] + box.radius.x;
    float Ymax = box.center.m128_f32[1] + box.radius.y;
    DirectX::XMFLOAT2 Pmax = { Xmax,Ymax };
    //�ŏ��_
    float Xmin = box.center.m128_f32[0] - box.radius.x;
    float Ymin = box.center.m128_f32[1] - box.radius.y;
    DirectX::XMFLOAT2 Pmin = { Xmin,Ymin };
    //�v���C���[�̒��S���W
    DirectX::XMFLOAT2 SpherePos = { sphere.center.m128_f32[0],sphere.center.m128_f32[1] };

    //�������̍��W��2DBox��2���_�̍��W�Ŕ�������
    if (SpherePos.x > Pmin.x && SpherePos.x < Pmax.x)
    {
        if (SpherePos.y + sphere.radius > Pmin.y && SpherePos.y - sphere.radius < Pmax.y)
        {
           return true;
        }
    }

    return false;
}

bool Collision::CheckBox2DBox2D(const Box& box1, const Box& box2)
{
    //�ő�_1
    float X1max = box1.center.m128_f32[0] + box1.radius.x;
    float Y1max = box1.center.m128_f32[1] + box1.radius.y;
    DirectX::XMFLOAT2 P1max = { X1max,Y1max };
    //�ŏ��_1
    float X1min = box1.center.m128_f32[0] - box1.radius.x;
    float Y1min = box1.center.m128_f32[1] - box1.radius.y;
    DirectX::XMFLOAT2 P1min = { X1min,Y1min };

    //�ő�_2
    float X2max = box2.center.m128_f32[0] + box2.radius.x;
    float Y2max = box2.center.m128_f32[1] + box2.radius.y;
    DirectX::XMFLOAT2 P2max = { X2max,Y2max };
    //�ŏ��_2
    float X2min = box2.center.m128_f32[0] - box2.radius.x;
    float Y2min = box2.center.m128_f32[1] - box2.radius.y;
    DirectX::XMFLOAT2 P2min = { X2min,Y2min };
    //�����d�Ȃ����Ȃ�
    if (P1max.y < P2max.y && P1max.y > P2min.y ||
        P1min.y < P2max.y && P1min.y > P2min.y)
    {
        if (P1max.x > P2min.x && P1max.x < P2max.x ||
            P1min.x > P2min.x && P1min.x < P2max.x)
        {
            return true;
        }
    }

    return false;
}
