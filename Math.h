#pragma once
#include <math.h>
#include <DirectXMath.h>
using namespace DirectX;

#include "Vector3.h"
#include "Matrix4.h"

namespace MathFunc {

	const float PI = 3.141592f;

	namespace Affine {
		//ワールド変換行列を設定する関数
		void SetMatScale(Matrix4& affineMat, Vector3 scale);				//スケーリング行列を設定する関数
		void SetMatRotation(Matrix4& affineMat, Vector3 rotation);			//回転行列を設定する関数
		void SetMatTranslation(Matrix4& affineMat, Vector3 translation);	//平行移動行列の設定をする関数

		//ワールド変換行列を生成する関数
		Matrix4 CreateMatScale(Vector3 scale);				//スケーリング行列を生成する関数
		Matrix4 CreateMatRotation(Vector3 rotation);		//回転行列を生成する関数
		Matrix4 CreateMatTranslation(Vector3 translation);	//平行移動行列の生成をする関数

	}

	namespace Utility {
		//XMMATRIXをMatrix4に変換する関数
		Matrix4 ConvertXMMATRIXtoMatrix4(XMMATRIX xmMatrix);

		//ビュー行列を生成する関数
		Matrix4 CreatMatView(Vector3 eye, Vector3 target, Vector3 up);

		//ベクトルと行列の掛け算をする関数
		Vector3 MulVector3AndMatrix4(Vector3 vec, Matrix4 mat);

	}
}