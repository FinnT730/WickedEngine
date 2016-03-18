#pragma once
#include "wiRenderer.h"
#include "wiColor.h"
#include "CommonInclude.h"


class wiTextureHelper
{
private:
	class wiTextureHelperInstance
	{
	private:
		enum HELPERTEXTURES
		{
			HELPERTEXTURE_RANDOM64X64,
			HELPERTEXTURE_COLORGRADEDEFAULT,
			HELPERTEXTURE_NORMALMAPDEFAULT,
			HELPERTEXTURE_COUNT
		};
		TextureView helperTextures[HELPERTEXTURE_COUNT];

		unordered_map<unsigned long, TextureView> colorTextures;
	public:
		wiTextureHelperInstance();
		~wiTextureHelperInstance();

		TextureView getRandom64x64();
		TextureView getColorGradeDefault();
		TextureView getNormalMapDefault();

		TextureView getWhite();
		TextureView getBlack();
		TextureView getTransparent();
		TextureView getColor(const wiColor& color);
	};

	static wiTextureHelperInstance* instance;

public:
	inline static wiTextureHelperInstance* getInstance()
	{
		if (instance != nullptr)
			return instance;

		return instance = new wiTextureHelperInstance();
	}

	template<typename T>
	static HRESULT CreateTexture(TextureView& texture, T* data, UINT width, UINT height, UINT channelCount, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM)
	{
		if (data == nullptr)
		{
			return E_FAIL;
		}

		Texture2DDesc textureDesc;
		ZeroMemory(&textureDesc, sizeof(textureDesc));
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = format;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = USAGE_DEFAULT;
		textureDesc.BindFlags = BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		ShaderResourceViewDesc shaderResourceViewDesc;
		shaderResourceViewDesc.Format = format;
		shaderResourceViewDesc.ViewDimension = RESOURCE_DIMENSION_TEXTURE2D;
		//shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		//shaderResourceViewDesc.Texture2D.MipLevels = 1;
		shaderResourceViewDesc.mipLevels = 1;

		SubresourceData InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = data;
		InitData.SysMemPitch = static_cast<UINT>(width * channelCount);

		Texture2D texture2D = nullptr;
		HRESULT hr;
		hr = wiRenderer::graphicsDevice->CreateTexture2D(&textureDesc, &InitData, &texture2D);
		if (FAILED(hr))
		{
			return hr;
		}
		hr = wiRenderer::graphicsDevice->CreateShaderResourceView(texture2D, &shaderResourceViewDesc, &texture);
		SAFE_RELEASE(texture2D);

		return hr;
	}
};

