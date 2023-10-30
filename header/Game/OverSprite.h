#include "header/2D/Sprite.h"
#include "header/Engin/Input.h"

class OverSprite
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="spriteCommon"></param>
	void Initialize(SpriteCommon* spriteCommon);
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="sceneNum_"></param>
	/// <param name="isBlackOut_"></param>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void Reset();
private:
	Sprite* overSprite;
private:
	bool isBlackOut = false;
};

