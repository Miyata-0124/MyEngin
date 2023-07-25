#include "CollisionManager.h"
#include "BaseCollider.h"
#include "Collision.h"

CollisionManager* CollisionManager::GetInstance()
{
    static CollisionManager instance;
    return &instance;
}

void CollisionManager::CheckAllCollisions()
{
    std::forward_list<BaseCollider*>::iterator colliderA;//����p�̃��X�g
    std::forward_list<BaseCollider*>::iterator colliderB;
    //��������`�F�b�N
    colliderA = colliders.begin();
    for (; colliderA != colliders.end(); ++colliderA) {
        colliderB = colliderA;
        ++colliderB;
        for (; colliderB != colliders.end(); ++colliderB) {
            BaseCollider* colA = *colliderA; //����1
            BaseCollider* colB = *colliderB; //����2

            //���ƕ���
            if (colA->GetShapeType() == COLISIONSHAPE_SPHERE && colB->GetShapeType() == COLISIONSHAPE_PLANE) {
                Sphere* SphereA = dynamic_cast<Sphere*>(colA);//�v���C���[,�A�C�e��
                Plane* PlaneA = dynamic_cast<Plane*>(colB);//��
                DirectX::XMVECTOR inter;//��_
                if (Collision::CheckSphere2Plane(*SphereA, *PlaneA, &inter)) {//���ƕ��ʂ̔���
                    colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
                    colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
                }
            }
            if (colB->GetShapeType() == COLISIONSHAPE_SPHERE && colA->GetShapeType() == COLISIONSHAPE_PLANE) {
                Sphere* SphereA = dynamic_cast<Sphere*>(colB);//�v���C���[,�A�C�e��
                Plane* PlaneA = dynamic_cast<Plane*>(colA);//��
                DirectX::XMVECTOR inter;//��_
                if (Collision::CheckSphere2Plane(*SphereA, *PlaneA, &inter)) {//���ƕ��ʂ̔���
                    colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
                    colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
                }
            }

            //���Ƌ�
            if (colA->GetShapeType() == COLISIONSHAPE_SPHERE && colB->GetShapeType() == COLISIONSHAPE_SPHERE)
            {
                Sphere* SphereA = dynamic_cast<Sphere*>(colA);//��1 �v���C���[
                Sphere* SphereB = dynamic_cast<Sphere*>(colB);//��2 �A�C�e��
                DirectX::XMVECTOR inter;//��_
                if (Collision::CheckSphere2Sphere(*SphereA, *SphereB, &inter)) {
                    colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
                    colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
                }
            }
        }
    }
}