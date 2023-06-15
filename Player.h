#pragma once
#include "Object3D.h"
#include "Model.h"

class Player
{
public:
	void Initialize(Model* model);
	void Update();
	void Draw();
private:
	Object3d* obj3d = new Object3d();

};

