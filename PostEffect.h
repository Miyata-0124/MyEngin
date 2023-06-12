#pragma once
#include "Sprite.h"
class PostEffect :
    public Sprite
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PostEffect();

    /// <summary>
    /// ������
    /// </summary>
    void initialize(DirectXCommon dxCommon);

    /// <summary>
    /// �`��R�}���h�̎��s
    /// </summary>
    /// <param name="cmdList"></param>
    void Draw();

private:
    // �e�N�X�`���o�b�t�@
    Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;
    // SRV�p�e�N�X�`���q�[�v
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
};

