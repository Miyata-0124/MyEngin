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
    /// 初期化
    /// </summary>
    void initialize(DirectXCommon dxCommon);

    /// <summary>
    /// 描画コマンドの実行
    /// </summary>
    /// <param name="cmdList"></param>
    void Draw();

private:
    // テクスチャバッファ
    Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
    // SRV用テクスチャヒープ
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
};

