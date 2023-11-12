#include "header/Game/Rain.h"

Rain* Rain::Create()
{
	//インスタンス生成
	Rain* instance = new Rain();
	if (instance == nullptr)
	{
		return nullptr;
	}
	//モデルセット
	instance->LoadTexture(texIndex, "blue1x1.png");

	//初期化
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
	//雨の基盤
	if (rainTimer < 10)
	{
		//パーティクル
		for (int i = 0; i < 15; i++)
		{
			//XYZ全て[-0.05f,+0.05f]でランダムに分布
			//const	float	rnd_vel = 1.5f;
			DirectX::XMFLOAT3	vel{};
			//vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

			//重力に見立ててYのみ[-0.001f,0]でランダムに分布
			const	float	rnd_acc = -0.1f;
			DirectX::XMFLOAT3	acc{};
			acc.y = (float)rand() / RAND_MAX * rnd_acc;

			Particle::Control(particleLife, { (float)rand() / RAND_MAX * 100.0f - 100.0f / 2.0f,40,0 }, vel, acc, 1.0f, 0.0f);
		}
	}

	Particle::Update();
}
