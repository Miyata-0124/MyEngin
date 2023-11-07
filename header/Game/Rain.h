#pragma once
#include "header/2D/Particle.h"

class Rain : public Particle
{
public:
	/// <summary>
	/// �I�u�W�F�N�g����
	/// </summary>
	/// <param name="model"></param>
	/// <returns></returns>
	static Rain* Create(uint32_t texIndex_);
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <returns></returns>
	bool Initialize(uint32_t texIndex_) override;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update()override;

private:
	//�J���Ǘ����鎞�v
	float rainTimer = 0.0f;
	bool rainFlag = false;
};
