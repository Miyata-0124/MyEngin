#pragma once
#include "Object3D.h"
#include "Model.h"
#include "Input.h"

class Player
{
public:
	void Initialize(Model* model);
	void Update(Input* input);
	void Draw();
	//�s��
	void Move(Input* input);
	//���Ⴊ�݂̍s��
	void CrouchMove(Input* input);
	//�d��
	void Gravity();
	//Getter,Setter
	XMFLOAT3 GetPosition() { return position; }

	XMMATRIX GetMatWorld() { return obj3d->GetMatWorld(); }
private:
	Object3d* obj3d;
	//���(�傫��,��]�p,���W)
	XMFLOAT3 scale;
	XMFLOAT3 rotation;
	XMFLOAT3 position;
	//���x
	XMFLOAT3 moveSpeed;//�ړ�
	XMFLOAT2 accelSpeed;//�������x
	float yadd;//�d��

	//��ԊǗ��t���O,�^�C�}�[
	bool isCrouche = false;
	bool isJump = false;
};

