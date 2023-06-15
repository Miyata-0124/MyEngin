#include "Player.h"

void Player::Initialize(Model* model)
{
	obj3d = Object3d::Create();
	obj3d->SetModel(model);
	obj3d->SetSize({ 2,2,2 });
	obj3d->SetPosition({ 15,0,0 });
}

void Player::Update()
{
	obj3d->Update();
}

void Player::Draw()
{
	obj3d->Draw();
}
