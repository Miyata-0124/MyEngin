#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include <DirectXMath.h>

class OBBCollider :public BaseCollider, public OBB
{
private: //�G�C���A�X
	//DirectX���ȗ�
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
	//�ꏊ
	XMVECTOR pos;
	//������
	XMVECTOR normalDir;
	//���̒���
	float dirLength[3];
};


