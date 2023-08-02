#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include <DirectXMath.h>

class OBBCollider :public BaseCollider, public OBB
{
private: //エイリアス
	//DirectXを省略
	using XMVECTOR = DirectX::XMVECTOR;
public:
	OBBCollider(XMVECTOR pos, XMVECTOR normalDir, float dirLength) :pos(pos), normalDir(normalDir)
	{
		shapeType = COLISIONSHAPE_OBB;
	}

	void Update()override;

	inline void SetDirLength(float dirLength) 
	{ 
		for (int i = 0; i < 3; i++)
		{
			this->dirLength[i] = dirLength;
		}
	}
private:
	//場所
	XMVECTOR pos;
	//方向軸
	XMVECTOR normalDir;
	//軸の長さ
	float dirLength[3];
};


