#include "header/2D/Sprite.h"
#include "header/Engin/Input.h"

class OverSprite
{
public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	/// <param name="spriteCommon"></param>
	void Initialize(SpriteCommon* spriteCommon);
	/// <summary>
	/// XV
	/// </summary>
	/// <param name="sceneNum_"></param>
	/// <param name="isBlackOut_"></param>
	void Update();
	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw();

	void Reset();
private:
	Sprite* overSprite;
private:
	bool isBlackOut = false;
};

