#include "Player.h"

void Player::Initialize(Model* model)
{
	obj3d = Object3d::Create();
	obj3d->SetModel(model);
	obj3d->SetSize({ 1,1,1 });
	obj3d->SetPosition({ 0,0,0 });
	//速度
	moveSpeed = { 0.5f,0.5f,0.5f };//移動
	accelSpeed = { 0.0f,0.0f };
	yadd = 0.0f;
	//状態管理フラグ,タイマー
}

void Player::Update(Input* input)
{
	//現在の情報を取得
	scale = obj3d->GetScale();
	rotation = obj3d->GetRotation();
	position = obj3d->GetPosition();

	Move(input);
	Gravity();
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
		if (scale.y != 1)
		{
			scale = { 1,1,1 };
		}
		if (isCrouche)
		{
			position.y += 0.5f;
		}
		isCrouche = false;
	}
	if (input->PushKey(DIK_DOWN)) // 下がる
	{
		//もし登り下り可能なパイプがあったなら座標を下げる
	}
	if (input->TriggerKey(DIK_DOWN))
	{
		if (scale.y != 0.5f)
		{
			scale = { 1,0.5,1 };
		}
		if (!isCrouche)
		{
			position.y -= 0.5f;
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
	if (isCrouche == false && isJump == false)
	{
		yadd = -1.0f;
		isJump = true;
	}
	if (isCrouche == true)
	{

	}
}

void Player::Gravity()
{
	position.y -= yadd;
	yadd += 0.2f;
	if (position.y<=-5.0f)
	{
		yadd = 0.0f;
		if (isJump)
		{
			isJump = false;
		}
	}
}
