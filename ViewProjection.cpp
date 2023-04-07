#include "ViewProjection.h"

void ViewProjection::Initialize()
{
	UpdateViewPro();		//matViewの初期化
	eye = { 0 , 0 , -50 };	//視点座標
	target = { 0 , 0 , 0 };	//注視点座標
	up = { 0 , 1 , 0 };		//上方向ベクトル
}

void ViewProjection::UpdateViewPro()
{
	matView = MathFunc::Utility::CreatMatView(eye, target, up);
}
