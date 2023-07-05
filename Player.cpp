#include "Player.h"

void Player::Initialize(Model* model)
{
	obj3d = Object3d::Create();
	obj3d->SetModel(model);
	obj3d->SetSize({ 2,2,2 });
	obj3d->SetPosition({ 0,0,0 });
	//速度
	moveSpeed = { 0.5f,0.5f,0.5f };//移動
	accelSpeed = { 0.0f,0.0f };
	yadd = { 0,0 };
	//状態管理フラグ,タイマー
}

void Player::Update(Input* input,bool isHit)
{
	//現在の情報を取得
	scale = obj3d->GetScale();
	rotation = obj3d->GetRotation();
	position = obj3d->GetPosition();

	Move(input);
	Gravity(isHit);
	//変更後の値をobjに渡す
	obj3d->SetSize(scale);
	obj3d->SetRotation(rotation);
	obj3d->SetPosition(position);
	obj3d->Update();
}

void Player::Draw()
{
	obj3d->Draw();
}

/// <summary>
/// 行動
/// </summary>
/// <param name="input">キー情報</param>
void Player::Move(Input* input)
{
	//取得した情報に値を追加していく
	if (input->PushKey(DIK_UP)) //登る
	{
		//もし登り下り可能なパイプがあったなら座標を上げる
	}
	if (input->TriggerKey(DIK_UP))
	{
		if (scale.y != 2)
		{
			scale = { 2,2,2 };
		}
		if (isCrouche)
		{
			position.y += 1;
		}
		isCrouche = false;
	}
	if (input->PushKey(DIK_DOWN)) // 下がる
	{
		//もし登り下り可能なパイプがあったなら座標を下げる
	}
	if (input->TriggerKey(DIK_DOWN))
	{
		if (scale.y != 1)
		{
			scale = { 2,1,2 };
		}
		if (!isCrouche)
		{
			position.y -= 1;
		}
		isCrouche = true;
	}
	if (input->PushKey(DIK_LEFT)) // 左に移動
	{
		position.x -= moveSpeed.x;
	}
	if (input->PushKey(DIK_RIGHT)) // 右に移動
	{
		position.x += moveSpeed.x;
	}
	if (input->TriggerKey(DIK_SPACE)) // ジャンプかスライド
	{
		CrouchMove(input);
	}
	
}

void Player::CrouchMove(Input* input)
{
	if (isCrouche == false)
	{
		yadd.y = -2.0f;
	}
	if (isCrouche == true)
	{

	}
}

void Player::Gravity(bool ishit)
{
	position.y -= yadd.y;
	yadd.y += 0.2f;
	if (ishit)
	{
		yadd.y = 0.0f;
	}
}
