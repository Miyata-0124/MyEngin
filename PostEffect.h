#pragma once
#include "Sprite.h"
class PostEffect :
    public Sprite
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PostEffect();

    /// <summary>
    /// 描画コマンドの実行
    /// </summary>
    /// <param name="cmdList"></param>
    void Draw();
};

