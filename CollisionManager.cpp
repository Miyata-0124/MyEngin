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
    std::forward_list<BaseCollider*>::iterator colliderA;//判定用のリスト
    std::forward_list<BaseCollider*>::iterator colliderB;
    //総当たりチェック
    colliderA = colliders.begin();
    for (; colliderA != colliders.end(); ++colliderA) {
        colliderB = colliderA;
        ++colliderB;
        for (; colliderB != colliders.end(); ++colliderB) {
            BaseCollider* colA = *colliderA; //判定1
            BaseCollider* colB = *colliderB; //判定2

            //球と平面
            if (colA->GetShapeType() == COLISIONSHAPE_SPHERE && colB->GetShapeType() == COLISIONSHAPE_PLANE) {
                Sphere* SphereA = dynamic_cast<Sphere*>(colA);//プレイヤー,アイテム
                Plane* PlaneA = dynamic_cast<Plane*>(colB);//床
                DirectX::XMVECTOR inter;//交点
                if (Collision::CheckSphere2Plane(*SphereA, *PlaneA, &inter)) {//球と平面の判定
                    colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
                    colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
                }
            }
            if (colB->GetShapeType() == COLISIONSHAPE_SPHERE && colA->GetShapeType() == COLISIONSHAPE_PLANE) {
                Sphere* SphereA = dynamic_cast<Sphere*>(colB);//プレイヤー,アイテム
                Plane* PlaneA = dynamic_cast<Plane*>(colA);//床
                DirectX::XMVECTOR inter;//交点
                if (Collision::CheckSphere2Plane(*SphereA, *PlaneA, &inter)) {//球と平面の判定
                    colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
                    colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
                }
            }

            //球と球
            if (colA->GetShapeType() == COLISIONSHAPE_SPHERE && colB->GetShapeType() == COLISIONSHAPE_SPHERE)
            {
                Sphere* SphereA = dynamic_cast<Sphere*>(colA);//球1 プレイヤー
                Sphere* SphereB = dynamic_cast<Sphere*>(colB);//球2 アイテム
                DirectX::XMVECTOR inter;//交点
                if (Collision::CheckSphere2Sphere(*SphereA, *SphereB, &inter)) {
                    colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
                    colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
                }
            }
        }
    }
}