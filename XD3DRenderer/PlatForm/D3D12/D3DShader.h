#pragma once

#include <unordered_map>
#include <wrl/client.h>
#include "D3D12Resource.h"
#include "D3D12RHI.h"

using Microsoft::WRL::ComPtr;

enum class EShaderType
{
	VERTEX_SHADER,
	PIXEL_SHADER,
	COMPUTE_SHADER,
};

struct XShaderDefines
{
public:
	void GetD3DShaderMacro(std::vector<D3D_SHADER_MACRO>& OutMacros) const;

	bool operator == (const XShaderDefines& Other) const;

	void SetDefine(const std::string& Name, const std::string& Definition);

public:
	std::unordered_map<std::string, std::string> DefinesMap;
};

// declare hash<XShaderDefines>
namespace std
{
	template <>
	struct hash<XShaderDefines>
	{
		std::size_t operator()(const XShaderDefines& Defines) const
		{
			using std::size_t;
			using std::hash;
			using std::string;
			// Compute individual hash values for each string 
			// and combine them using XOR
			// and bit shifting:

			size_t HashValue = 0;
			for (const auto& Pair : Defines.DefinesMap)
			{
				HashValue ^= (hash<string>()(Pair.first) << 1);
				HashValue ^= (hash<string>()(Pair.second) << 1);
			}

			return HashValue;
		}
	};
}

struct XShaderParameter
{
	std::string Name;
	EShaderType ShaderType;
	UINT BindPoint;
	UINT RegisterSpace;
};

struct XShaderCBVParameter : XShaderParameter
{
	D3D12ConstantBufferRef ConstantBufferRef;
};

struct XShaderSRVParameter : XShaderParameter
{
	UINT BindCount;

	std::vector<D3D12ShaderResourceView*> SRVList;
};

struct XShaderUAVParameter : XShaderParameter
{
	UINT BindCount;

	std::vector<D3D12UnorderedAccessView*> UAVList;
};

struct XShaderSamplerParameter : XShaderParameter
{

};

struct XShaderInfo
{
	std::string ShaderName;

	std::string FileName;

	XShaderDefines ShaderDefines;

	bool bCreateVS = false;

	std::string VSEntryPoint = "VS";

	bool bCreatePS = false;

	std::string PSEntryPoint = "PS";

	bool bCreateCS = false;

	std::string CSEntryPoint = "CS";
};

class D3DShader
{
public:
	D3DShader(const XShaderInfo& InShaderInfo, D3D12RHI* InD3D12RHI);

	void Initialize();

	bool SetParameter(std::string ParamName, D3D12ConstantBufferRef ConstantBufferRef);

	bool SetParameter(std::string ParamName, D3D12ShaderResourceView* SRV);

	bool SetParameter(std::string ParamName, const std::vector<D3D12ShaderResourceView*>& SRVList);

	bool SetParameter(std::string ParamName, D3D12UnorderedAccessView* UAV);

	bool SetParameter(std::string ParamName, const std::vector<D3D12UnorderedAccessView*>& UAVList);

	void BindParameters();

private:
	static Microsoft::WRL::ComPtr<ID3DBlob> CompileShader(const std::wstring& Filename, const D3D_SHADER_MACRO* Defines, const std::string& Entrypoint, const std::string& Target);

	void GetShaderParameters(ComPtr<ID3DBlob> PassBlob, EShaderType ShaderType);

	D3D12_SHADER_VISIBILITY GetShaderVisibility(EShaderType ShaderType);

	std::vector<CD3DX12_STATIC_SAMPLER_DESC> CreateStaticSamplers();

	void CreateRootSignature();

	void CheckBindings();

	void ClearBindings();

public:
	XShaderInfo ShaderInfo;

	std::vector<XShaderCBVParameter> CBVParams;

	std::vector<XShaderSRVParameter> SRVParams;

	std::vector<XShaderUAVParameter> UAVParams;

	std::vector<XShaderSamplerParameter> SamplerParams;

	int CBVSignatureBaseBindSlot = -1;

	int SRVSignatureBindSlot = -1;

	UINT SRVCount = 0;

	int UAVSignatureBindSlot = -1;

	UINT UAVCount = 0;

	int SamplerSignatureBindSlot = -1;

	std::unordered_map<std::string, ComPtr<ID3DBlob>> ShaderPass;

	ComPtr<ID3D12RootSignature> RootSignature;

private:
	D3D12RHI* XD3D12RHI = nullptr;
};