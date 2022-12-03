#include "D3D12DescriptorCache.h"
#include "D3D12Device.h"


D3D12DescriptorCache::D3D12DescriptorCache(D3D12Device* InDevice)
	:Device(InDevice)
{
	CreateCbvSrvUavDescriptorHeap();

	CreateRtvDescriptorHeap();
}

D3D12DescriptorCache::~D3D12DescriptorCache()
{

}

void D3D12DescriptorCache::CreateCbvSrvUavDescriptorHeap()
{
	D3D12_DESCRIPTOR_HEAP_DESC CSUHeapDesc;
	CSUHeapDesc.NumDescriptors = MaxCbvSrvUavDescripotrCount;
	CSUHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	CSUHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	ThrowIfFailed(Device->GetD3DDevice()->CreateDescriptorHeap(&CSUHeapDesc, IID_PPV_ARGS(&CbvSrvUavDescriptorHeap)));
	SetDebugName(CbvSrvUavDescriptorHeap.Get(), L"D3D12DescriptorCache CbvSrvUavDescriptorHeap");

	CbvSrvUavDescriptorSize = Device->GetD3DDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}


CD3DX12_GPU_DESCRIPTOR_HANDLE D3D12DescriptorCache::AppendCbvSrvUavDescriptorHeap(const std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>& SrcDescriptors)
{
	// Append to heap
	uint32_t SlotsNeeded = (uint32_t)SrcDescriptors.size();
	assert(CbvSrvUavDescriptorOffset + SlotsNeeded < MaxCbvSrvUavDescripotrCount);

	auto CpuDescriptorHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(CbvSrvUavDescriptorHeap
		->GetCPUDescriptorHandleForHeapStart(), CbvSrvUavDescriptorOffset, CbvSrvUavDescriptorSize);
	Device->GetD3DDevice()->CopyDescriptors(1, &CpuDescriptorHandle, &SlotsNeeded, SlotsNeeded, SrcDescriptors.data(), 
		nullptr, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// Get GpuDescriptorHandle
	auto GpuDescriptorHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(CbvSrvUavDescriptorHeap
		->GetGPUDescriptorHandleForHeapStart(), CbvSrvUavDescriptorOffset, CbvSrvUavDescriptorSize);

	// Increase descriptor offset
	CbvSrvUavDescriptorOffset += SlotsNeeded;

	return GpuDescriptorHandle;
}

void D3D12DescriptorCache::ResetCbvSrvUavDescriptorHeap()
{
	CbvSrvUavDescriptorOffset = 0;
}

void D3D12DescriptorCache::CreateRtvDescriptorHeap()
{
	// Create the descriptor heap.
	D3D12_DESCRIPTOR_HEAP_DESC RtvHeapDesc = {};
	RtvHeapDesc.NumDescriptors = MaxRtvDescriptorCount;
	RtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	RtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	ThrowIfFailed(Device->GetD3DDevice()->CreateDescriptorHeap(&RtvHeapDesc, IID_PPV_ARGS(&RtvDescriptorHeap)));
	SetDebugName(RtvDescriptorHeap.Get(), L"D3D12DescriptorCache RtvDescriptorHeap");

	RtvDescriptorSize = Device->GetD3DDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
}

void D3D12DescriptorCache::AppendRtvDescriptors(const std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>& RtvDescriptors,CD3DX12_GPU_DESCRIPTOR_HANDLE& OutGpuHandle, CD3DX12_CPU_DESCRIPTOR_HANDLE& OutCpuHandle)
{
	// Append to heap
	uint32_t SlotsNeeded = (uint32_t)RtvDescriptors.size();
	assert(RtvDescriptorOffset + SlotsNeeded < MaxRtvDescriptorCount);

	auto CpuDescriptorHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(RtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), RtvDescriptorOffset, RtvDescriptorSize);
	Device->GetD3DDevice()->CopyDescriptors(1, &CpuDescriptorHandle,
		&SlotsNeeded, SlotsNeeded, RtvDescriptors.data(), nullptr, D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	OutGpuHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(RtvDescriptorHeap->GetGPUDescriptorHandleForHeapStart(), 
		RtvDescriptorOffset, RtvDescriptorSize);

	OutCpuHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(RtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), 
		RtvDescriptorOffset, RtvDescriptorSize);

	// Increase descriptor offset
	RtvDescriptorOffset += SlotsNeeded;
}

void D3D12DescriptorCache::ResetRtvDescriptorHeap()
{
	RtvDescriptorOffset = 0;
}

void D3D12DescriptorCache::CreateDsvDescriptorHeap()
{
	// Create the descriptor heap.
	D3D12_DESCRIPTOR_HEAP_DESC RtvHeapDesc = {};
	RtvHeapDesc.NumDescriptors = MaxDsvDescriptorCount;
	RtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	RtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	ThrowIfFailed(Device->GetD3DDevice()->CreateDescriptorHeap(&RtvHeapDesc, IID_PPV_ARGS(&DsvDescriptorHeap)));
	SetDebugName(RtvDescriptorHeap.Get(), L"D3D12DescriptorCache DsvDescriptorHeap");

	RtvDescriptorSize = Device->GetD3DDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
}

void D3D12DescriptorCache::AppendDsvDescriptors(const std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>& DsvDescriptors, CD3DX12_GPU_DESCRIPTOR_HANDLE& OutGpuHandle, CD3DX12_CPU_DESCRIPTOR_HANDLE& OutCpuHandle)
{
	// Append to heap
	uint32_t SlotsNeeded = (uint32_t)DsvDescriptors.size();
	assert(DsvDescriptorOffset + SlotsNeeded < MaxDsvDescriptorCount);

	auto CpuDescriptorHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(DsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), DsvDescriptorOffset, DsvDescriptorSize);
	Device->GetD3DDevice()->CopyDescriptors(1, &CpuDescriptorHandle,
		&SlotsNeeded, SlotsNeeded, DsvDescriptors.data(), nullptr, D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

	OutGpuHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(DsvDescriptorHeap->GetGPUDescriptorHandleForHeapStart(),
		DsvDescriptorOffset, DsvDescriptorSize);

	OutCpuHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(DsvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
		DsvDescriptorOffset, DsvDescriptorSize);

	// Increase descriptor offset
	DsvDescriptorOffset += SlotsNeeded;
}

void D3D12DescriptorCache::ResetDsvDescriptorHeap()
{
	DsvDescriptorOffset = 0;
}




void D3D12DescriptorCache::Reset()
{
	ResetCbvSrvUavDescriptorHeap();

	ResetRtvDescriptorHeap();

	ResetDsvDescriptorHeap();
}