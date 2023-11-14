#pragma once
#include "header/Game/GameBaseScene.h"

class GameSceneManager
{
public: 
	/// <summary>
	/// �X�V
	/// </summary>
	void  Update(ViewProjection* camera_,Input* input_);
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
public:
	//�f�X�g���N�^
	~GameSceneManager();

	//�V�[���̗\��
	void SetNextScene(GameBaseScene* nextScene_) { nextScene = nextScene_; }
private:
	//���s���̃V�[��
	GameBaseScene* scene = nullptr;
	//���̃V�[��
	GameBaseScene* nextScene = nullptr;
};

