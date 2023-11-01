#include "header/2D/Sprite.h"
#include "header/Engin/Input.h"

class OverSprite
{
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="spriteCommon"></param>
	void Initialize(SpriteCommon* spriteCommon);
	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="sceneNum_"></param>
	/// <param name="isBlackOut_"></param>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	void Reset();
private:
	Sprite* overSprite;
	Sprite* blackOut;
private:
	bool isBlackOut = false;
	//�Q�[���I�[�o�[���~���Ă���^�C�}�[
	float downTimer = 0.0f;
	//�C�[�W���O�p
	float min = 0.0f;
	float max = 1.0f;
	float startY = 0.0f;
	float endY =  300.0f;
	float y;
	//�X����p
	float rotStartZ = 0.0f;
	float rotEndZ = 10.0f;
	float rotSpeed = 0.0f;
	bool rotDir = false;
	float z;
	//�A���t�@�l
	bool isAlpha = false;
	float alphaTimer = 0.0f;
	float alpha = 0.0f;
	int alphaCount = 0;

};

