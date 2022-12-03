#pragma once

#include <string>
#include "TextureInfo.h"
#include "../PlatForm/D3D12/D3D12Texture.h"
#include "../PlatForm/D3D12/D3D12RHI.h"


struct XTextureResource
{
	XTextureInfo TextureInfo;

	std::vector<uint8_t> TextureData;

	std::vector<D3D12_SUBRESOURCE_DATA> InitData;
};

class XTexture
{
public:
	XTexture(const std::string& InName, ETextureType InType, bool InbSRGB, std::wstring InFilePath)
		:Name(InName), Type(InType), bSRGB(InbSRGB), FilePath(InFilePath)
	{}

	virtual ~XTexture()
	{}

	XTexture(const XTexture& Other) = delete;

	XTexture& operator=(const XTexture& Other) = delete;

public:
	void LoadTextureResourceFromFlie(D3D12RHI* D3D12RHI);

	void SeXTextureResourceDirectly(const XTextureInfo& InTextureInfo, const std::vector<uint8_t>& InTextureData,
		const D3D12_SUBRESOURCE_DATA& InInitData);

	void CreateTexture(D3D12RHI* D3D12RHI);


private:
	static std::wstring GetExtension(std::wstring path);

	void LoadDDSTexture(D3D12Device* Device);

	void LoadWICTexture(D3D12Device* Device);

	void LoadHDRTexture(D3D12Device* Device);

public:
	std::string Name;

	ETextureType Type;

	std::wstring FilePath;

	bool bSRGB = true;

	XTextureResource TextureResource;

};

class XTexture2D : public XTexture
{
public:
	XTexture2D(const std::string& InName, bool InbSRGB, std::wstring InFilePath);

	~XTexture2D();
};

class XTextureCube : public XTexture
{
public:
	XTextureCube(const std::string& InName, bool InbSRGB, std::wstring InFilePath);

	~XTextureCube();
};
