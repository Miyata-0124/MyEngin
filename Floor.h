#pragma once
#include "Object3D.h"
#include "Model.h"

class Floor : public Object3d
{
public:
	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static Floor* Create(Model* model = nullptr);

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <returns></returns>
	bool Initialize() override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

	/// <summary>
	/// �R�[���o�b�N
	/// </summary>
	/// <param name="info"></param>
	void OnCollider(const CollisionInfo& info)override;
private:
	//���_����̋���
	float distance = -7.0f;
	//���a
	float radius = 0.5f;
//public:
//	void Initialize(Model* model);
//	void Update();
//	void Draw();
//
//	//Getter,Setter
//	XMFLOAT3 GetPosition() { return position; }
//
//	XMMATRIX GetMatWorld() { return obj3d->GetMatWorld(); }
//private:
//	Object3d* obj3d;
//	//���(�傫��,��]�p,���W)
//	XMFLOAT3 scale;
//	XMFLOAT3 rotation;
//	XMFLOAT3 position;
};

