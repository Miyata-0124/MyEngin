#include "header/Engin/DirectXCommon.h"

#include<cassert>
#include<vector>
#pragma	comment(lib, "d3d12.lib")
#pragma	comment(lib,"dxgi.lib")

using	namespace Microsoft::WRL;


//�f�o�C�X�̏�����
void DirectXCommon::InitializeDevice() {
#ifdef _DEBUG
	//�f�o�b�N���C���[��I���ɂ���
	ComPtr < ID3D12Debug1> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(true);
	}
#endif


	//ComPtr < ID3D12Device> device = nullptr;
	//ComPtr<	IDXGIFactory7> dxgiFactory = nullptr;


	//DXGI�t�@�N�g���[�̐���
	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	assert(SUCCEEDED(result));

	//�A�_�v�^�[�̗񌟋�
	std::vector< ComPtr<IDXGIAdapter4>>adapters;
	//�����ɓ���̖��O����A�_�v�^�[�I�u�W�F�N�g������
	ComPtr < IDXGIAdapter4> tmpAdapter = nullptr;
	//�p�t�H�[�}���X��������̂��珇�ɁA�S�ẴA�_�v�^�[��񋓂���
	for (UINT i = 0;
		dxgiFactory->EnumAdapterByGpuPreference
		(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
			IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND; i++)
	{
		// ���I�z��ɒǉ�����
		adapters.push_back(tmpAdapter);
	}
	//�Ó��ȃA�_�v�^��I�ʂ���
	for (size_t i = 0; i < adapters.size(); i++)
	{
		DXGI_ADAPTER_DESC3	adapterDesc;
		//�A�_�v�^�[�̏���擾����
		adapters[i]->GetDesc3(&adapterDesc);

		//�\�t�g�E�F�A�f�o�C�X����
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE))
		{
			//�f�o�C�X��̗p���ă��[�v�𔲂���
			tmpAdapter = adapters[i];
			break;
		}
	}
	//�Ή����x���̔z��
	D3D_FEATURE_LEVEL	levels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};
	D3D_FEATURE_LEVEL	featureLevel;
	for (size_t i = 0; i < _countof(levels); i++)
	{
		//�̗p�����A�_�v�^�[�Ńf�o�C�X�𐶐�
		result = D3D12CreateDevice(tmpAdapter.Get(), levels[i],
			IID_PPV_ARGS(&device));
		if (result == S_OK)
		{
			//�f�o�C�X�𐶐��ł������_�Ń��[�v�𔲂���
			featureLevel = levels[i];
			break;
		}

	}


}
//�R�}���h�̏�����
void DirectXCommon::InitializeCommand() {
	//�R�}���h�A���P�[�^�𐶐�
	result = device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&cmdAllocator));
	assert(SUCCEEDED(result));

	//�R�}���h���X�g�𐶐�
	result = device->CreateCommandList(
		0, D3D12_COMMAND_LIST_TYPE_DIRECT,
		cmdAllocator.Get(), nullptr,
		IID_PPV_ARGS(&comList));
	assert(SUCCEEDED(result));


	//�R�}���h�L���[�𐶐�
	result = device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	assert(SUCCEEDED(result));
}
//�X���b�v�`�F�[���̏�����
void DirectXCommon::InitializeSwapchain() {

	swapChainDesc.Width = 1280;
	swapChainDesc.Height = 720;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//IDXGISwapChain1��ComPtr��p��
	//�X���b�v�`�F�[���̐���
	result = dxgiFactory->CreateSwapChainForHwnd(
		commandQueue.Get(),
		winApp->GetHwnd(),
		&swapChainDesc,
		nullptr,
		nullptr,
		&swapChain1);
	//��������IDXGISwapChan1�̃I�u�W�F�N�g��IDXGISwapChain4�ɕϊ�����
	swapChain1.As(&swapChain);

	assert(SUCCEEDED(result));
}
//�����_�[�^�[�Q�b�g�r���[�̏�����
void DirectXCommon::InitializeRenderTargetView() {
	//�f�X�N���v�^�q�[�v�̐ݒ�
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount;

	//�f�X�N���v�^�q�[�v�̐���
	device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));

	//�o�b�N�o�b�t�@
	backBuffers.resize(swapChainDesc.BufferCount);

	//�X���b�v�`�F�[���̑S�Ẵo�b�t�@�ɂ��ď�������
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		//�X���b�v�`�F�[������o�b�t�@��擾 
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		//�f�X�N���v�^�q�[�v�̃n���h����擾 
		D3D12_CPU_DESCRIPTOR_HANDLE	rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		// �����\�ŃA�h���X�������
		rtvHandle.ptr += i * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		// �����_�[�^�[�Q�b�g�r���[�̐ݒ�
		D3D12_RENDER_TARGET_VIEW_DESC	rtvDesc{};
		// �V�F�[�_�[�̌v�Z���ʂ�SRGB�ɕϊ����ď�������
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		// �����_�[�^�[�Q�b�g�r���[�̐���
		device->CreateRenderTargetView(backBuffers[i].Get(), &rtvDesc, rtvHandle);
	}
}
//�[�x�o�b�t�@�̏�����
void DirectXCommon::InitializeDepthBuffer() {
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC	depthResourceDesc{};
	depthResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthResourceDesc.Width = WinApp::window_width;//�����_�[�^�[�Q�b�g�ɍ��킹��
	depthResourceDesc.Height = WinApp::window_height;//�����_�[�^�[�Q�b�g�ɍ��킹��
	depthResourceDesc.DepthOrArraySize = 1;
	depthResourceDesc.Format = DXGI_FORMAT_D32_FLOAT;//�[�x�l�t�H�[�}�b�g
	depthResourceDesc.SampleDesc.Count = 1;
	depthResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;//�f�v�X�X�e���V��
	//�[�x�l�p�q�[�v�v���p�e�B
	D3D12_HEAP_PROPERTIES depthHeapProp{};
	depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	//�[�x�l�̃N���A�ݒ�
	D3D12_CLEAR_VALUE	depthClearValue{};
	depthClearValue.DepthStencil.Depth = 1.0f;//�[�x�l1.0���i�ő�l�j�ŃN���A
	depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;//�[�x�l�t�H�[�}�b�g
	//���\�[�X�ݒ�

	result = device->CreateCommittedResource(
		&depthHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&depthResourceDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,//�[�x�l�������݂Ɏg�p
		&depthClearValue,
		IID_PPV_ARGS(&depthBuff));

	//�[�x�r���[�p�f�X�N���v�^�q�[�v�쐬
	dsvHeapDesc.NumDescriptors = 1;//�[�x�r���[��1��
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;	//�f�v�X�X�e���V���r���[

	result = device->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));
	//�[�x�r���[�쐬
	D3D12_DEPTH_STENCIL_VIEW_DESC	dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;//�[�x�l�t�H�[�}�b�g
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	device->CreateDepthStencilView(
		depthBuff.Get(),
		&dsvDesc,
		dsvHeap->GetCPUDescriptorHandleForHeapStart());
}
//�t�F���X�̏�����
void DirectXCommon::InitializeFence() {
	//�t�F���X�̐���
	fence = nullptr;
	fenceVal = 0;

	result = device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
}

//�`��O����
void DirectXCommon::PreDraw() {
	// �o�b�N�o�b�t�@�̔ԍ���擾(2�Ȃ̂�0�Ԃ�1��)
	UINT bbIndex = swapChain->GetCurrentBackBufferIndex();

	// 1.���\�[�X�o���A�ŏ������݉\�ɕύX
	barrierDesc.Transition.pResource = backBuffers[bbIndex].Get(); // �o�b�N�o�b�t�@��w��
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT; // �\����Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET; // �`���Ԃ�
	comList->ResourceBarrier(1, &barrierDesc);

	// 2.�`���̕ύX
	// �����_�[�^�[�Q�b�g�r���[�̃n���h����擾
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
	rtvHandle.ptr += bbIndex * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
	D3D12_CPU_DESCRIPTOR_HANDLE	dsvHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();
	comList->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

	// 3.��ʃN���A R G B A
	//�l��������ނƎ����I�ɓ]�������
	FLOAT clearColor[4] = { 0.0f,0.0f,0.0f,1.0f }; // ���ۂ��F
	comList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	comList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
	//�X�y�[�X�L�[��������Ă�����
	//if (key[DIK_SPACE])
	//{
	//	FLOAT clearColor[] = { 0.5f,0.5f, 0.5f,0.0f };
	//	comList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	//}
	// 4.�`��R�}���h��������

	// �r���[�|�[�g�ݒ�R�}���h
	D3D12_VIEWPORT viewport{};
	viewport.Width = WinApp::window_width;
	viewport.Height = WinApp::window_height;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	// �r���[�|�[�g�ݒ�R�}���h��A�R�}���h���X�g�ɐς�
	comList->RSSetViewports(1, &viewport);

	//�V�U�[��`
	D3D12_RECT	scissorRect{};
	scissorRect.left = 0;                                       // �؂蔲�����W��
	scissorRect.right = scissorRect.left + WinApp::window_width;        // �؂蔲�����W�E
	scissorRect.top = 0;                                        // �؂蔲�����W��
	scissorRect.bottom = scissorRect.top + WinApp::window_height;       // �؂蔲�����W��
	// �V�U�[��`�ݒ�R�}���h��A�R�}���h���X�g�ɐς�
	comList->RSSetScissorRects(1, &scissorRect);
}
//�`��㏈��
void DirectXCommon::PostDraw() {
	// �o�b�N�o�b�t�@�̔ԍ���擾(2�Ȃ̂�0�Ԃ�1��)
	UINT bbIndex = swapChain->GetCurrentBackBufferIndex();

	barrierDesc.Transition.pResource = backBuffers[bbIndex].Get(); // �o�b�N�o�b�t�@��w��
	// 5.���\�[�X�o���A��߂�
	barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET; // �`���Ԃ���
	barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT; // �\����Ԃ�
	comList->ResourceBarrier(1, &barrierDesc);

	// ���߂̃N���[�Y
	result = comList->Close();
	assert(SUCCEEDED(result));
	// �R�}���h���X�g�̎��s
	ID3D12CommandList* commandLists[] = { comList.Get() };
	commandQueue->ExecuteCommandLists(1, commandLists);
	// ��ʂɕ\������o�b�t�@��t���b�v(���\�̓��ւ�)

	result = swapChain->Present(1, 0);
	//assert(SUCCEEDED(result));

	// �R�}���h�̎��s������҂�
	commandQueue->Signal(fence.Get(), ++fenceVal);
	if (fence->GetCompletedValue() != fenceVal) {
		HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		fence->SetEventOnCompletion(fenceVal, event);
		WaitForSingleObject(event, INFINITE);
		CloseHandle(event);
	}
	// �L���[��N���A
	result = cmdAllocator->Reset();
	assert(SUCCEEDED(result));
	// �ĂуR�}���h���X�g�𒙂߂鏀��
	result = comList->Reset(cmdAllocator.Get(), nullptr);
	assert(SUCCEEDED(result));
}

void DirectXCommon::Initialize(WinApp* winApp_) {
	//NULL���o
	assert(winApp_);
	//�����o�ϐ��ɑ��
	this->winApp = winApp_;
	//�f�o�C�X�̏�����
	InitializeDevice();
	//�R�}���h�̏�����
	InitializeCommand();
	//�X���b�v�`�F�[���̏�����
	InitializeSwapchain();
	//�����_�[�^�[�Q�b�g�r���[�̏�����
	InitializeRenderTargetView();
	//�[�x�o�b�t�@�̏�����
	InitializeDepthBuffer();
	//�t�F���X�̏�����
	InitializeFence();

#ifdef _DEBUG


	ComPtr < ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&infoQueue))))
	{
		//�}������G���[
		D3D12_MESSAGE_ID	denyIds[] = {
			D3D12_MESSAGE_ID_RESOURCE_BARRIER_MISMATCHING_COMMAND_LIST_TYPE
		};
		//�}������\�����x��
		D3D12_MESSAGE_SEVERITY	severities[] = { D3D12_MESSAGE_SEVERITY_INFO };
		D3D12_INFO_QUEUE_FILTER	filter{};
		filter.DenyList.NumIDs = _countof(denyIds);
		filter.DenyList.pIDList = denyIds;
		filter.DenyList.NumSeverities = _countof(severities);
		filter.DenyList.pSeverityList = severities;
		//�w�肵���G���[�̕\����}������
		infoQueue->PushStorageFilter(&filter);

		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
		infoQueue->Release();
	}
#endif
}