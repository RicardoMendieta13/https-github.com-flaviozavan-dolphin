// Copyright 2013 Dolphin Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include "VideoBackends/D3D/D3DTexture.h"
#include "VideoCommon/TextureCacheBase.h"

namespace DX11
{

class TextureCache : public ::TextureCache
{
public:
	TextureCache();
	~TextureCache();

private:
	struct TCacheEntry : TCacheEntryBase
	{
		D3DTexture2D *const texture;

		D3D11_USAGE usage;

		inline TCacheEntry(D3DTexture2D *_tex, u32 width, u32 height, u32 _num_mipmaps, bool _is_efb_copy)
		: TCacheEntryBase(width, height, _num_mipmaps, _is_efb_copy), texture(_tex) {}
		~TCacheEntry();

		void Load(unsigned int width, unsigned int height,
			unsigned int expanded_width, unsigned int levels);

		void FromRenderTarget(u32 dstAddr, unsigned int dstFormat,
			unsigned int srcFormat, const EFBRectangle& srcRect,
			bool isIntensity, bool scaleByHalf, unsigned int cbufid,
			const float *colmat);

		void Bind(unsigned int stage);
		bool Save(const std::string filename, unsigned int level);
	};

	TCacheEntryBase* CreateTexture(unsigned int width, unsigned int height,
		unsigned int tex_levels);

	TCacheEntryBase* CreateRenderTargetTexture(unsigned int scaled_tex_w, unsigned int scaled_tex_h);
	u64 EncodeToRamFromTexture(u32 address, void* source_texture, u32 SourceW, u32 SourceH, bool bFromZBuffer, bool bIsIntensityFmt, u32 copyfmt, int bScaleByHalf, const EFBRectangle& source) {return 0;};
};

}
