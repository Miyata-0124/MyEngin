#include "PostEffect.h"
#include <d3dx12.h>

using namespace DirectX;

//インデックスデータ
unsigned short postIndices[] = {
	0,1,2,
	1,2,3,
};

PostEffect::PostEffect()
	: Sprite()
{
}

void PostEffect::Draw()
{
	//srvHeap = spriteCommon->GetSrvHeap();
	comList = directXCom->GetCommandList();
	matWorld = XMMatrixIdentity();
	//matWorld.r[0].m128_f32[0] = 2.0f / directXCom->GetSwapChainDesc().Width;
	//matWorld.r[1].m128_f32[1] = -2.0f / directXCom->GetSwapChainDesc().Height;
	//matWorld *= XMMatrixScaling(1.0f, 1.0f, 0.0f);
	matWorld *= XMMatrixRotationZ(XMConvertToRadians(rotation));
	matWorld *= XMMatrixTranslation(position.x, position.y, 0.0f);

	constMap->color = color;
	constMap->mat = matWorld * matProjection;

	//非表示
	if (isInvisible)
	{
		return;
	}

	spriteCommon->SetTextureCommands(texIndex);

	// 頂点バッファビューの設定コマンド
	comList->IASetVertexBuffers(0, 1, &vbView);
	//定数バッファビュー（CBV）の設定コマンド
	comList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());


	//インディックスバッファビューの設定コマンド
	comList->IASetIndexBuffer(&ibView);
	//定数バッファビュー(CBV)の設定コマンド
	//comList->SetGraphicsRootConstantBufferView(2, constBuff->GetGPUVirtualAddress());
	// 描画コマンド
	comList->DrawIndexedInstanced(_countof(postIndices), texIndex, 0, 0, 0);//全ての頂点を使って描画
}
