#include "ViewProjection.h"

void ViewProjection::Initialize()
{
	UpdateViewPro();		//matView�̏�����
	eye = { 0 , 0 , -50 };	//���_���W
	target = { 0 , 0 , 0 };	//�����_���W
	up = { 0 , 1 , 0 };		//������x�N�g��
}

void ViewProjection::UpdateViewPro()
{
	matView = MathFunc::Utility::CreatMatView(eye, target, up);
}
