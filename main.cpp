#include "GameScene.h"

//windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int	WINAPI	WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {


	GameScene* gameScene = new GameScene();
	gameScene->Initialize();
#pragma	endregion
	//�X�V����
	while (true)
	{

#pragma region ���b�Z�[�W
		if (gameScene->GetWinApp()->ProcessMessage()) {
			break;
		}
#pragma endregion

#pragma region ���t���[������

		gameScene->Update();
		//-------------------�`�揈��-------------------

		gameScene->Draw();
		//Direct���t���[�������@�����܂�
#pragma endregion
		if (gameScene->GetInput()->PushKey(DIK_ESCAPE))
		{
			break;
		}
	}
#pragma	region	�ŏ��̃V�[���̏I��
	gameScene->Finalize();
#pragma	endregion
	return 0;
}