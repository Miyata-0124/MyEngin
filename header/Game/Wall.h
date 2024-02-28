/**
 * @file Wall.h
 * @brief �ǂ̋@�\
 * @author �~���^_�R�E�L
 * @date 2023/10/10
 */

#pragma once
#include "header/3D/Object3D.h"

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

	//�Q�b�^�[,�Z�b�^�[
private:

};

