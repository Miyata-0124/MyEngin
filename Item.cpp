#include "Item.h"

void Item::Initialize(Model* model)
{
	obj3d = Object3d::Create();
	obj3d->SetModel(model);
	obj3d->SetSize({ 1,2,1 });
	obj3d->SetPosition({ 0,-5,0 });
}

void Item::Update()
{
	//Œ»Ý‚Ìî•ñ‚ðŽæ“¾
	scale = obj3d->GetScale();
	rotation = obj3d->GetRotation();
	position = obj3d->GetPosition();



	//•ÏXŒã‚Ì’l‚ðobj‚É“n‚·
	obj3d->SetSize(scale);
	obj3d->SetRotation(rotation);
	obj3d->SetPosition(position);
	obj3d->Update();
}

void Item::Draw()
{
	obj3d->Draw();
}
