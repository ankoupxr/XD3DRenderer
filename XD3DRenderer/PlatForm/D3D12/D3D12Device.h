#pragma once
#include "D3D12Util.h"


class D3D12RHI;

class D3D12Device
{
public:
	D3D12Device(D3D12RHI* InD3D12RHI);
	~D3D12Device();

	ID3D12Device* GetD3DDevice() { return D3DDevice.Get(); }

	D3D12CommandContext* GetCommandContext() { return CommandContext.get(); }

	ID3D12CommandQueue* GetCommandQueue() { return CommandContext->GetCommandQueue(); }

	ID3D12GraphicsCommandList* GetCommandList() { return CommandContext->GetCommandList(); }

	TD3D12UploadBufferAllocator* GetUploadBufferAllocator() { return UploadBufferAllocator.get(); }

	TD3D12DefaultBufferAllocator* GetDefaultBufferAllocator() { return DefaultBufferAllocator.get(); }

	TD3D3TextureResourceAllocator* GetTextureResourceAllocator() { return TextureResourceAllocator.get(); }

	TD3D12HeapSlotAllocator* GetHeapSlotAllocator(D3D12_DESCRIPTOR_HEAP_TYPE HeapType);

private:

	void Initialize();

	Microsoft::WRL::ComPtr<ID3D12Device> D3DDevice = nullptr;

	std::unique_ptr<TD3D12CommandContext> CommandContext = nullptr;
	std::unique_ptr<TD3D12UploadBufferAllocator> UploadBufferAllocator = nullptr;

	std::unique_ptr<TD3D12DefaultBufferAllocator> DefaultBufferAllocator = nullptr;

	std::unique_ptr<TD3D3TextureResourceAllocator> TextureResourceAllocator = nullptr;

	std::unique_ptr<TD3D12HeapSlotAllocator> RTVHeapSlotAllocator = nullptr;

	std::unique_ptr<TD3D12HeapSlotAllocator> DSVHeapSlotAllocator = nullptr;

	std::unique_ptr<TD3D12HeapSlotAllocator> SRVHeapSlotAllocator = nullptr;
};
