#include "GameScene.h"
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	GameScene gameScene;

	gameScene.Initialize();
	//ゲームループ
	while (true) {

		//Windowsのメッセージ処理
		if (gameScene.GetWinApp()->ProcessMesseage()) {
			//ゲームループを抜ける
			break;
		}

		gameScene.Update();

		gameScene.Draw();

	}

	gameScene.Finalize();

	return 0;
}