// Copyright 2013 Dolphin Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include "VideoCommon/TextureCacheBase.h"

namespace Null
{

class TextureCache : public ::TextureCache
{
public:
	TextureCache() {}

private:
	struct TCacheEntry : TCacheEntryBase
	{
		TCacheEntry() {}
		~TCacheEntry() {}

		void Load(unsigned int width, unsigned int height,
			unsigned int expanded_width, unsigned int level) override {}

		void FromRenderTarget(u32 dstAddr, unsigned int dstFormat,
			PEControl::PixelFormat srcFormat, const EFBRectangle& srcRect,
			bool isIntensity, bool scaleByHalf, unsigned int cbufid,
			const float *colmat) override {}

		void Bind(unsigned int stage) override {}

		bool Save(const std::string& filename, unsigned int level) override {return false;}
	};

	~TextureCache() {}
	TCacheEntryBase* CreateTexture(unsigned int width, unsigned int height,
		unsigned int expanded_width, unsigned int tex_levels, PC_TexFormat pcfmt) override
	{
		return new TCacheEntry;
	}

	TCacheEntryBase* CreateRenderTargetTexture(unsigned int scaled_tex_w, unsigned int scaled_tex_h) override
	{
		return new TCacheEntry;
	}
};

} // Null name space
