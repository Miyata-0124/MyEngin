#pragma once
#include "Object3D.h"
/// <summary>
/// �����o����A�C�e��(�΂⑄�Ȃ�)
/// </summary>
class Item : public Object3d
{
public:
	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static Item* Create(Model* model = nullptr);

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

	//�ێ��ł��邩�ǂ����̃t���O���擾
	bool GetRetention() { return isRetention; }

private:
	void Gravity();

private:
	//�d�͉��Z��
	float yadd = 0.0f;
	//���a
	float radius = 0.6f;

	//�^�C�}�[,�t���O
	bool isRetention = false;
};