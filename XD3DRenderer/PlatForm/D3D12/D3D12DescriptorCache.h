#pragma once

#include "D3D12Util.h"

class D3D12Device;

//描述符管理
class D3D12DescriptorCache
{
public:
	D3D12DescriptorCache(D3D12Device* InDevice);
	~D3D12DescriptorCache();

	//返回常量缓冲区视图、着色器资源视图、无序访问视图
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetCbvSrvUavDescriptorHeap() { return CbvSrvUavDescriptorHeap; }
	//添加常量缓冲区视图、着色器资源视图、无序访问视图到描述符堆
	CD3DX12_GPU_DESCRIPTOR_HANDLE AppendCbvSrvUavDescriptorHeap(const std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>& SrcDescriptors);
	//返回渲染目标视图
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetRtvDescriptorHeap() { return RtvDescriptorHeap; }
	//添加渲染目标视图到描述符堆
	void AppendRtvDescriptors(const std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>& RtvDescriptors,
		CD3DX12_GPU_DESCRIPTOR_HANDLE& OutGpuHandle, CD3DX12_CPU_DESCRIPTOR_HANDLE& OutCpuHandle);
	//返回渲染目标视图
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetDsvDescriptorHeap() { return DsvDescriptorHeap; }
	//添加渲染目标视图到描述符堆
	void AppendDsvDescriptors(const std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>& RtvDescriptors,
		CD3DX12_GPU_DESCRIPTOR_HANDLE& OutGpuHandle, CD3DX12_CPU_DESCRIPTOR_HANDLE& OutCpuHandle);
	void Reset();



private:
	D3D12Device* Device = nullptr;

	UINT CbvSrvUavDescriptorSize;
	static const int MaxCbvSrvUavDescripotrCount = 2048;
	uint32_t CbvSrvUavDescriptorOffset = 0;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CbvSrvUavDescriptorHeap = nullptr;


	UINT RtvDescriptorSize;
	static const int MaxRtvDescriptorCount = 1024;
	uint32_t RtvDescriptorOffset = 0;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> RtvDescriptorHeap = nullptr;

	UINT DsvDescriptorSize;
	static const int MaxDsvDescriptorCount = 1024;
	uint32_t DsvDescriptorOffset = 0;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> DsvDescriptorHeap = nullptr;

	//创建常量缓冲区视图、着色器资源视图、无序访问视图
	void CreateCbvSrvUavDescriptorHeap();
	//创建渲染目标视图
	void CreateRtvDescriptorHeap();
	//创建深度视图
	void CreateDsvDescriptorHeap();
	//清空该描述符堆
	void ResetCbvSrvUavDescriptorHeap();
	void ResetRtvDescriptorHeap();
	void ResetDsvDescriptorHeap();
};
