#include "GameScene.h"

//windowsアプリでのエントリーポイント(main関数)
int	WINAPI	WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {


	GameScene* gameScene = new GameScene();
	gameScene->Initialize();
#pragma	endregion
	//更新処理
	while (true)
	{

#pragma region メッセージ
		if (gameScene->GetWinApp()->ProcessMessage()) {
			break;
		}
#pragma endregion

#pragma region 毎フレーム処理

		gameScene->Update();
		//-------------------描画処理-------------------

		gameScene->Draw();
		//Direct毎フレーム処理　ここまで
#pragma endregion
		if (gameScene->GetInput()->PushKey(DIK_ESCAPE))
		{
			break;
		}
	}
#pragma	region	最初のシーンの終了
	gameScene->Finalize();
#pragma	endregion
	return 0;
}