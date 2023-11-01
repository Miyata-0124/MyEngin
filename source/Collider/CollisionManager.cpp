#include "header/Collider/CollisionManager.h"
#include "header/Collider/BaseCollider.h"
#include "header/Collider/Collision.h"

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
            //���ƕ��� 
            else if (colB->GetShapeType() == COLISIONSHAPE_SPHERE && colA->GetShapeType() == COLISIONSHAPE_PLANE) {
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
                if (Collision::CheckSphere2Sphere(*SphereA, *SphereB)) {
                    colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
                    colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
                }
            }
            //����2D�l�p
            if (colA->GetShapeType() == COLISIONSHAPE_SPHERE && colB->GetShapeType() == COLISIONSHAPE_BOX) {
                Sphere* SphereA = dynamic_cast<Sphere*>(colA);
                Box* BoxA = dynamic_cast<Box*>(colB);
                DirectX::XMVECTOR inter;//��_
                if (Collision::CheckSphere2Box2D(*SphereA, *BoxA)){
                    colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
                    colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
                }
            }
            else if (colB->GetShapeType() == COLISIONSHAPE_SPHERE && colA->GetShapeType() == COLISIONSHAPE_BOX) {
                Sphere* SphereA = dynamic_cast<Sphere*>(colB);
                Box* BoxA = dynamic_cast<Box*>(colA);
                DirectX::XMVECTOR inter;//��_
                if (Collision::CheckSphere2Box2D(*SphereA, *BoxA)) {
                    colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
                    colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
                }
            }
        }
    }
}