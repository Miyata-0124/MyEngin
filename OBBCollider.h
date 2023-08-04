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
	OBBCollider(XMVECTOR offset = { 0,0,0,0 }, XMVECTOR size = { 0,0,0,0 }, XMVECTOR rot[3] = 0)
	{
		//�`��Z�b�g
		shapeType = COLISIONSHAPE_OBB;
	}
	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

private:
	//���S���W
	XMVECTOR center = { 0,0,0,1 };
	//�e���W���̌X���x�N�g��
	XMVECTOR rot[3] = { 0,0,0,0 };
	//OBB���W���̒�������
	XMVECTOR size = { 1,1,1,1 };
};


