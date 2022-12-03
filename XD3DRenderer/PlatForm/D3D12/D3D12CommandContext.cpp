#include "D3D12CommandContext.h"
#include "D3D12Device.h"

D3D12CommandContext::D3D12CommandContext(D3D12Device* InDevice)
	:Device(InDevice)
{
	CreateCommandContext();
	DescriptorCache = std::make_unique<D3D12DescriptorCache>(Device);
}

D3D12CommandContext::~D3D12CommandContext()
{
	DestroyCommandContext();
}

void D3D12CommandContext::CreateCommandContext() 
{
	//创建围栏
	ThrowIfFailed(Device->GetD3DDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&Fence)));
	//创建命令队列
	D3D12_COMMAND_QUEUE_DESC QueueDesc = {};
	QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	QueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	ThrowIfFailed(Device->GetD3DDevice()->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&CommandQueue)));
	//创建命令分配器
	ThrowIfFailed(Device->GetD3DDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(CommandListAlloc.GetAddressOf())));
	//创建命令列表
	ThrowIfFailed(Device->GetD3DDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, CommandListAlloc.Get(),
		nullptr, IID_PPV_ARGS(CommandList.GetAddressOf())));
	//凡是调用重置函数，CommandList必须关闭
	ThrowIfFailed(CommandList->Close());

}

void D3D12CommandContext::ResetCommandAllocator()
{
	ThrowIfFailed(CommandListAlloc->Reset());
}

void D3D12CommandContext::ResetCommandList()
{
	ThrowIfFailed(CommandList->Reset(CommandListAlloc.Get(), nullptr));
}

void D3D12CommandContext::ExecuteCommandLists()
{

	ThrowIfFailed(CommandList->Close());

	// Add the command list to the queue for execution.
	ID3D12CommandList* cmdsLists[] = { CommandList.Get() };
	CommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
}

void D3D12CommandContext::FlushCommandQueue()
{
	CurrentFenceValue++;

	ThrowIfFailed(CommandQueue->Signal(Fence.Get(), CurrentFenceValue));

	if (Fence->GetCompletedValue() < CurrentFenceValue)
	{
		HANDLE eventHandle = CreateEvent(nullptr, false, false, nullptr);
 
		ThrowIfFailed(Fence->SetEventOnCompletion(CurrentFenceValue, eventHandle));

		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}
}

void D3D12CommandContext::EndFrame()
{
	DescriptorCache->Reset();
}