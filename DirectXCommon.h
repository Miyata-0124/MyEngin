#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include<cassert>
#include<vector>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include<vector>
#include<thread>
#include"WinApp.h"
#include<chrono>


#pragma once
class DirectXCommon
{
public://�����o�֐�
	//������
	void Initialize(WinApp* winApp_);
	//�f�o�C�X�̏�����
	void InitializeDevice();
	//�R�}���h�̏�����
	void InitializeCommand();
	//�X���b�v�`�F�[���̏�����
	void InitializeSwapchain();
	//�����_�[�^�[�Q�b�g�r���[
	void InitializeRenderTargetView();
	//�[�x�o�b�t�@�̏�����
	void InitializeDepthBuffer();
	//�t�F���X�̏�����
	void InitializeFence();

	//�`��O����
	void PreDraw();
	//�`��㏈��
	void PostDraw();

	//�f�o�C�X�̎擾
	ID3D12Device* GetDevice()const { return device.Get(); }
	//�R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* GetCommandList()const { return comList.Get(); }

	//result
	HRESULT GetResult()const { return result; }
private: // �����o�֐�
	// FPS�Œ菉����
	void InitializeFixFPS();
	// FPS�Œ�X�V
	void UpdateFixFPS();
	// �L�^����(FPS�Œ�p)
	std::chrono::steady_clock::time_point reference_;
private:
	//DirectX12�f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device>device;
	//DXGI�t�@�N�g��
	Microsoft::WRL::ComPtr<IDXGIFactory7>dxgiFactory;
	//�R�}���h�L���[�̐ݒ�
	D3D12_COMMAND_QUEUE_DESC	commandQueueDesc{};
	Microsoft::WRL::ComPtr<IDXGISwapChain4>swapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>cmdAllocator = nullptr;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>comList = nullptr;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue>commandQueue = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>rtvHeap = nullptr;
	//�X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1	swapChainDesc{};
	//�o�b�N�o�b�t�@
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>>backBuffers;
	//�f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC	rtvHeapDesc{};
	//�[�x�r���[�p�f�X�N���v�^�q�[�v�쐬
	D3D12_DESCRIPTOR_HEAP_DESC	dsvHeapDesc{};
	//�[�x�r���[�p�f�X�N���v�^�q�[�v�쐬
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>dsvHeap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;
	//�t�F���X�̐���
	Microsoft::WRL::ComPtr<ID3D12Fence>fence = nullptr;
	UINT64	fenceVal = 0;
	//���\�[�X�o���A
	D3D12_RESOURCE_BARRIER barrierDesc{};
private:
	WinApp* winApp = nullptr;
	HRESULT	result;
};
