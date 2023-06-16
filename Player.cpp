#include "Player.h"

void Player::Initialize(Model* model)
{
	obj3d = Object3d::Create();
	obj3d->SetModel(model);
	obj3d->SetSize({ 2,2,2 });
	obj3d->SetPosition({ 0,0,0 });
	//移動速度
	moveSpeed = { 0.5f,0.5f,0.5f };
	//姿勢管理フラグ
	downPosture = false;
}

void Player::Update(Input* input)
{
	Move(input);
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
	//現在の座標を取得
	position = obj3d->GetPosition();
	//取得した情報に値を追加していく
	if (input->PushKey(DIK_UP)) //登る
	{
		//もし登り下り可能なパイプがあったなら座標を上げる
	}
	if (input->PushKey(DIK_DOWN)) // 下がる
	{
		//もし登り下り可能なパイプがあったなら座標を下げる
	}
	if (input->PushKey(DIK_LEFT)) // 左に移動
	{
		position.x -= moveSpeed.x;
	}
	if (input->PushKey(DIK_RIGHT)) // 右に移動
	{
		position.x += moveSpeed.x;
	}
	if (input->TriggerKey(DIK_SPACE)) // ジャンプ
	{

	}
	//変更後の値をobjに渡す
	obj3d->SetPosition({ position.x,position.y,position.z });
}
