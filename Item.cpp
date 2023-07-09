#include "Item.h"

void Item::Initialize(Model* model)
{
	obj3d = Object3d::Create();
	obj3d->SetModel(model);
	obj3d->SetSize({ 0.5f,0.5f,0.5f });
	obj3d->SetPosition({ 5,0,0});

	yadd = 0.0f;
}

void Item::Update()
{
	//現在の情報を取得
	scale = obj3d->GetScale();
	rotation = obj3d->GetRotation();
	position = obj3d->GetPosition();

	Gravity();

	//変更後の値をobjに渡す
	obj3d->SetSize(scale);
	obj3d->SetRotation(rotation);
	obj3d->SetPosition(position);
	obj3d->Update();
}

void Item::Draw()
{
	obj3d->Draw();
}

void Item::Gravity()
{
	position.y -= yadd;
	yadd += 0.2f;
	if (position.y <= -5.0f)
	{
		yadd = 0.0f;
	}
}
