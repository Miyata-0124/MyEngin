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
    std::forward_list<BaseCollider*>::iterator sphereA;
    std::forward_list<BaseCollider*>::iterator sphereB;
    std::forward_list<BaseCollider*>::iterator planeA;
    std::forward_list<BaseCollider*>::iterator rayA;
    //総当たりチェック
    sphereA = colliders.begin();
    for (; sphereA != colliders.end(); ++sphereA) {
        planeA = sphereA;
        ++planeA;
        for (; planeA != colliders.end(); ++planeA) {
            BaseCollider* colA = *sphereA; //Sphere
            BaseCollider* colB = *planeA; //Plane
            if (colA->GetShapeType() == COLISIONSHAPE_SPHERE && colB->GetShapeType() == COLISIONSHAPE_PLANE) {
                Sphere* SphereA = dynamic_cast<Sphere*>(colA);
                Plane* PlaneA = dynamic_cast<Plane*>(colB);
                DirectX::XMVECTOR inter;
                if (Collision::CheckSphere2Plane(*SphereA, *PlaneA, &inter)) {
                    colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
                    colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
                }
            }
        }
    }
    /*sphereA = colliders.begin();
    for (; sphereA != colliders.end(); ++sphereA) {
        sphereB = sphereA;
        ++sphereB;
        for (; sphereB != colliders.end(); ++sphereB) {
            BaseCollider* colA = *sphereA;
            BaseCollider* colB = *sphereB;

            if (colA->GetShapeType() == COLISIONSHAPE_SPHERE && colB->GetShapeType() == COLISIONSHAPE_SPHERE) {
                Sphere* SphereA = dynamic_cast<Sphere*>(colA);
                Sphere* SphereB = dynamic_cast<Sphere*>(colB);
                DirectX::XMVECTOR inter;
                if (Collision::CheckSphere2Sphere(*SphereA, *SphereB,&inter)) {
                    colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
                    colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
                }
            }
        }
    }
    rayA = colliders.begin();
    for (; rayA != colliders.end(); ++rayA) {
        planeA = rayA;
        ++planeA;
        for (; planeA != colliders.end(); ++planeA) {
            BaseCollider* colA = *rayA;
            BaseCollider* colB = *planeA;
            if (colA->GetShapeType() == COLISIONSHAPE_RAY && colB->GetShapeType() == COLISIONSHAPE_PLANE) {
                Ray* RayA = dynamic_cast<Ray*>(colA);
                Plane* PlaneA = dynamic_cast<Plane*>(colB);
                float distance;
                DirectX::XMVECTOR inter;
                if (Collision::CheckRay2Plane(*RayA, *PlaneA, &distance, &inter)) {
                    colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
                    colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
                }

            }
        }
    }*/
}