#include "PlaneCollider.h"

using namespace DirectX;
void PlaneCollider::Update()
{
	//ワールド行列から座標抽出
	const XMMATRIX& matWorld = object3d->GetMatWorld();

	//平面のメンバ変数を更新
	//法線ベクトル
	Plane::normal = { 0,1,0,0 };
	//原点からの距離()
	Plane::distance = distance;
}