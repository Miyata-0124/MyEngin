#include "Floor.h"

void Floor::Initialize(Model* model)
{
	obj3d = Object3d::Create();
	obj3d->SetModel(model);
	obj3d->SetSize({ 40,1,40 });
	obj3d->SetPosition({ 0,-10,0 });
}

void Floor::Update()
{
	obj3d->Update();
}

void Floor::Draw()
{
	obj3d->Draw();
}
