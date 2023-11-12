#include "header/Game/Rain.h"

Rain* Rain::Create()
{
	//�C���X�^���X����
	Rain* instance = new Rain();
	if (instance == nullptr)
	{
		return nullptr;
	}
	//���f���Z�b�g
	instance->LoadTexture(texIndex, "blue1x1.png");

	//������
	if (!instance->Initialize(texIndex)) {
		delete instance;
		assert(0);
	}

	return instance;
}

bool Rain::Initialize(uint32_t texIndex_)
{
	if (!Particle::Initialize(texIndex_))
	{
		return false;
	}
	
    return true;
}

void Rain::Update()
{
	if (rainTimer < 10)
	{
		rainTimer++;
	}
	else
	{
		rainTimer = 0;
	}
	//�J�̊��
	if (rainTimer < 10)
	{
		//�p�[�e�B�N��
		for (int i = 0; i < 15; i++)
		{
			//XYZ�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
			//const	float	rnd_vel = 1.5f;
			DirectX::XMFLOAT3	vel{};
			//vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

			//�d�͂Ɍ����Ă�Y�̂�[-0.001f,0]�Ń����_���ɕ��z
			const	float	rnd_acc = -0.1f;
			DirectX::XMFLOAT3	acc{};
			acc.y = (float)rand() / RAND_MAX * rnd_acc;

			Particle::Control(particleLife, { (float)rand() / RAND_MAX * 100.0f - 100.0f / 2.0f,40,0 }, vel, acc, 1.0f, 0.0f);
		}
	}

	Particle::Update();
}
