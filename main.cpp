#include "GameScene.h"
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	GameScene gameScene;

	gameScene.Initialize();
	//�Q�[�����[�v
	while (true) {

		//Windows�̃��b�Z�[�W����
		if (gameScene.GetWinApp()->ProcessMesseage()) {
			//�Q�[�����[�v�𔲂���
			break;
		}

		gameScene.Update();

		gameScene.Draw();

	}

	gameScene.Finalize();

	return 0;
}