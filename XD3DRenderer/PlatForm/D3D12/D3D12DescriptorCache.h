#pragma once

#include "D3D12Util.h"

class D3D12Device;

//����������
class D3D12DescriptorCache
{
public:
	D3D12DescriptorCache(D3D12Device* InDevice);
	~D3D12DescriptorCache();

	//���س�����������ͼ����ɫ����Դ��ͼ�����������ͼ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetCbvSrvUavDescriptorHeap() { return CbvSrvUavDescriptorHeap; }
	//��ӳ�����������ͼ����ɫ����Դ��ͼ�����������ͼ����������
	CD3DX12_GPU_DESCRIPTOR_HANDLE AppendCbvSrvUavDescriptorHeap(const std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>& SrcDescriptors);
	//������ȾĿ����ͼ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetRtvDescriptorHeap() { return RtvDescriptorHeap; }
	//�����ȾĿ����ͼ����������
	void AppendRtvDescriptors(const std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>& RtvDescriptors,
		CD3DX12_GPU_DESCRIPTOR_HANDLE& OutGpuHandle, CD3DX12_CPU_DESCRIPTOR_HANDLE& OutCpuHandle);
	//������ȾĿ����ͼ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> GetDsvDescriptorHeap() { return DsvDescriptorHeap; }
	//�����ȾĿ����ͼ����������
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

	//����������������ͼ����ɫ����Դ��ͼ�����������ͼ
	void CreateCbvSrvUavDescriptorHeap();
	//������ȾĿ����ͼ
	void CreateRtvDescriptorHeap();
	//���������ͼ
	void CreateDsvDescriptorHeap();
	//��ո���������
	void ResetCbvSrvUavDescriptorHeap();
	void ResetRtvDescriptorHeap();
	void ResetDsvDescriptorHeap();
};
