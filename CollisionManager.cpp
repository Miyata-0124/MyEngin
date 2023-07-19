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
    std::forward_list<BaseCollider*>::iterator colliderA;//����p1�ڂ̃��X�g
    std::forward_list<BaseCollider*>::iterator colliderB;//2�ڂ̃��X�g
    //��������`�F�b�N
    colliderA = colliders.begin();
    for (; colliderA != colliders.end(); ++colliderA) {
        colliderB = colliderA;
        ++colliderB;
        for (; colliderB != colliders.end(); ++colliderB) {
            BaseCollider* colA = *colliderA; //����1
            BaseCollider* colB = *colliderB; //����2
            if (colA->GetShapeType() == COLISIONSHAPE_SPHERE && colB->GetShapeType() == COLISIONSHAPE_PLANE) {
                Sphere* SphereA = dynamic_cast<Sphere*>(colA);//��
                Plane* PlaneA = dynamic_cast<Plane*>(colB);//����
                DirectX::XMVECTOR inter;//��_
                if (Collision::CheckSphere2Plane(*SphereA, *PlaneA, &inter)) {//���ƕ��ʂ̔���
                    colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
                    colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
                }
            }

            if (colA->GetShapeType() == COLISIONSHAPE_SPHERE && colB->GetShapeType() == COLISIONSHAPE_SPHERE) {
                Sphere* SphereA = dynamic_cast<Sphere*>(colA);//��1
                Sphere* SphereB = dynamic_cast<Sphere*>(colB);//��2
                DirectX::XMVECTOR inter;//��_
                if (Collision::CheckSphere2Sphere(*SphereA, *SphereB, &inter)) { //���B�̔���
                    colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
                    colA->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
                }
            }
        }
    }
}