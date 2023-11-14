#pragma once
#include "header/Engin/ViewProjection.h"
#include "header/Engin/Input.h"

class GameSceneManager;

class GameBaseScene
{
public:

	virtual void Initialize(ViewProjection* camera_,Input* input_);

	virtual void Finalize();

	virtual void Update();

	virtual void Draw();

public: //ƒƒ“ƒoŠÖ”
	virtual ~GameBaseScene() = default;
	virtual void SetScanManager(GameSceneManager* sceneManager_) { sceneManager = sceneManager_; }
protected:
	GameSceneManager* sceneManager = nullptr;
};

