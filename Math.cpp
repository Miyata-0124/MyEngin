#include "Math.h"
#include <stdlib.h>

//�X�P�[�����O�s���ݒ肷��֐�
void MathFunc::Affine::SetMatScale(Matrix4& affineMat, Vector3 scale) {
	//�X�P�[�����O�s���錾
	Matrix4 matScale = {
		scale.x , 0 , 0 , 0 ,
		0 , scale.y , 0 , 0 ,
		0 , 0 , scale.z , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//�s��̌v�Z
	affineMat *= matScale;

}

//��]�s���ݒ肷��֐�
void MathFunc::Affine::SetMatRotation(Matrix4& affineMat, Vector3 rotation) {

	//��]�s���錾
	//Z����]
	Matrix4 matRotZ = {
		(float)cos(rotation.z) , (float)sin(rotation.z) , 0 , 0 ,
		(float)-sin(rotation.z) , (float)cos(rotation.z) , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//X����]
	Matrix4 matRotX = {
		1 , 0 , 0 , 0 ,
		0 , (float)cos(rotation.x) , (float)sin(rotation.x) , 0 ,
		0 , -(float)sin(rotation.x) , (float)cos(rotation.x) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//Y����]
	Matrix4 matRotY = {
		(float)cos(rotation.y) , 0 , (float)-sin(rotation.y) , 0 ,
		0 , 1 , 0 , 0 ,
		(float)sin(rotation.y) , 0 , (float)cos(rotation.y) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//�s��̌v�Z
	affineMat *= matRotX;
	affineMat *= matRotY;
	affineMat *= matRotZ;

}

//���s�ړ��s��̐ݒ������֐�
void MathFunc::Affine::SetMatTranslation(Matrix4& affineMat, Vector3 translation) {

	//���s�ړ��s��̐錾
	Matrix4 matTranslation = {
		1 , 0 , 0 , 0 ,
		0 , 1 , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		translation.x , translation.y , translation.z , 1 ,
	};

	//�s��̌v�Z
	affineMat *= matTranslation;
}
#pragma endregion

#pragma region//���[���h�ϊ��s��𐶐�����֐�
//�X�P�[�����O�s��𐶐�����֐�
Matrix4 MathFunc::Affine::CreateMatScale(Vector3 scale) {

	//�X�P�[�����O�s���錾
	Matrix4 matScale = {
		scale.x , 0 , 0 , 0 ,
		0 , scale.y , 0 , 0 ,
		0 , 0 , scale.z , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//�s��̌v�Z
	return matScale;

}

//��]�s��𐶐�����֐�
Matrix4 MathFunc::Affine::CreateMatRotation(Vector3 rotation) {

	//��]�s���錾
	Matrix4 matRot;
	matRot.SetIdentityMatrix();

	//Z����]
	Matrix4 matRotZ = {
		(float)cos(rotation.z) , (float)sin(rotation.z) , 0 , 0 ,
		(float)-sin(rotation.z) , (float)cos(rotation.z) , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//X����]
	Matrix4 matRotX = {
		1 , 0 , 0 , 0 ,
		0 , (float)cos(rotation.x) , (float)sin(rotation.x) , 0 ,
		0 , (float)-sin(rotation.x) , (float)cos(rotation.x) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//Y����]
	Matrix4 matRotY = {
		(float)cos(rotation.y) , 0 , (float)-sin(rotation.y) , 0 ,
		0 , 1 , 0 , 0 ,
		(float)sin(rotation.y) , 0 , (float)cos(rotation.y) , 0 ,
		0 , 0 , 0 , 1 ,
	};

	//�s��̌v�Z
	matRot *= matRotZ;
	matRot *= matRotX;
	matRot *= matRotY;

	return matRot;

}


//���s�ړ��s��̐���������֐�
Matrix4 MathFunc::Affine::CreateMatTranslation(Vector3 translation) {

	//���s�ړ��s��̐錾
	Matrix4 matTranslation = {
		1 , 0 , 0 , 0 ,
		0 , 1 , 0 , 0 ,
		0 , 0 , 1 , 0 ,
		translation.x , translation.y , translation.z , 1 ,
	};

	//�s��̌v�Z
	return matTranslation;
}

#pragma endregion

//XMMATRIX��Matrix4�ɕϊ�����֐�
Matrix4 MathFunc::Utility::ConvertXMMATRIXtoMatrix4(XMMATRIX xmMatrix) {
	Matrix4 matrix4;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			matrix4.m[i][j] = xmMatrix.r[i].m128_f32[j];

		}
	}

	return matrix4;
}

//�r���[�s��𐶐�����֐�
Matrix4 MathFunc::Utility::CreatMatView(Vector3 eye, Vector3 target, Vector3 up) {

	Matrix4 matView;

	XMFLOAT3 xmEye;
	xmEye.x = eye.x;
	xmEye.y = eye.y;
	xmEye.z = eye.z;

	XMFLOAT3 xmTarget;
	xmTarget.x = target.x;
	xmTarget.y = target.y;
	xmTarget.z = target.z;

	XMFLOAT3 xmUp;
	xmUp.x = up.x;
	xmUp.y = up.y;
	xmUp.z = up.z;

	XMMATRIX xmMatView = XMMatrixLookAtLH(
		XMLoadFloat3(&xmEye), XMLoadFloat3(&xmTarget), XMLoadFloat3(&xmUp));

	xmMatView *= XMMatrixPerspectiveFovLH(XM_PIDIV2, 1280 / 720, 1.0f, 100.0f);

	matView = MathFunc::Utility::ConvertXMMATRIXtoMatrix4(xmMatView);

	return matView;

}

//�x�N�g���ƍs��̊|���Z������֐�
Vector3  MathFunc::Utility::MulVector3AndMatrix4(Vector3 vec, Matrix4 mat) {

	Vector3 ans;

	ans.x =
		mat.m[0][0] * vec.x +
		mat.m[1][0] * vec.y +
		mat.m[2][0] * vec.z +
		mat.m[3][0] * 0;

	ans.y =
		mat.m[0][1] * vec.x +
		mat.m[1][1] * vec.y +
		mat.m[2][1] * vec.z +
		mat.m[3][1] * 0;

	ans.z =
		mat.m[0][2] * vec.x +
		mat.m[1][2] * vec.y +
		mat.m[2][2] * vec.z +
		mat.m[3][2] * 0;

	return ans;

}