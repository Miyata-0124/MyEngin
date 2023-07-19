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
    std::forward_list<BaseCollider*>::iterator colliderA;//判定用1個目のリスト
    std::forward_list<BaseCollider*>::iterator colliderB;//2個目のリスト
    //総当たりチェック
    colliderA = colliders.begin();
    for (; colliderA != colliders.end(); ++colliderA) {
        colliderB = colliderA;
        ++colliderB;
        for (; colliderB != colliders.end(); ++colliderB) {
            BaseCollider* colA = *colliderA; //判定1
            BaseCollider* colB = *colliderB; //判定2
            if (colA->GetShapeType() == COLISIONSHAPE_SPHERE && colB->GetShapeType() == COLISIONSHAPE_PLANE) {
                Sphere* SphereA = dynamic_cast<Sphere*>(colA);//球
                Plane* PlaneA = dynamic_cast<Plane*>(colB);//平面
                DirectX::XMVECTOR inter;//交点
                if (Collision::CheckSphere2Plane(*SphereA, *PlaneA, &inter)) {//球と平面の判定
                    colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
                    colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
                }
            }

            if (colA->GetShapeType() == COLISIONSHAPE_SPHERE && colB->GetShapeType() == COLISIONSHAPE_SPHERE) {
                Sphere* SphereA = dynamic_cast<Sphere*>(colA);//球1
                Sphere* SphereB = dynamic_cast<Sphere*>(colB);//球2
                DirectX::XMVECTOR inter;//交点
                if (Collision::CheckSphere2Sphere(*SphereA, *SphereB, &inter)) { //球達の判定
                    colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
                    colA->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
                }
            }
        }
    }
}