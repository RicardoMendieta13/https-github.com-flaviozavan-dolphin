// Copyright 2013 Dolphin Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#include "VideoCommon/IndexGenerator.h"
#include "VideoCommon/Statistics.h"
#include "VideoCommon/VideoConfig.h"

#include "VideoBackends/NULL/PixelShaderCache.h"
#include "VideoBackends/NULL/VertexManager.h"
#include "VideoBackends/NULL/VertexShaderCache.h"

// internal state for loading vertices
extern NativeVertexFormat *g_nativeVertexFmt;

namespace Null
{

class NullNativeVertexFormat : public NativeVertexFormat
{
public:
	NullNativeVertexFormat() {}
	void Initialize(const PortableVertexDeclaration &vtx_decl) override {}
	void SetupVertexPointers() override {}
};

NativeVertexFormat* VertexManager::CreateNativeVertexFormat()
{
	return new NullNativeVertexFormat;
}

VertexManager::VertexManager()
{
	LocalVBuffer.resize(MAXVBUFFERSIZE);
	LocalIBuffer.resize(MAXIBUFFERSIZE);
}

VertexManager::~VertexManager()
{
}

void VertexManager::ResetBuffer(u32 stride)
{
	s_pCurBufferPointer = s_pBaseBufferPointer = LocalVBuffer.data();
	s_pEndBufferPointer = s_pCurBufferPointer + LocalVBuffer.size();
	IndexGenerator::Start(GetIndexBuffer());
}

void VertexManager::vFlush(bool useDstAlpha)
{
	PixelShaderCache::SetShader(
		useDstAlpha ? DSTALPHA_DUAL_SOURCE_BLEND : DSTALPHA_NONE,
		g_nativeVertexFmt->m_components);
	VertexShaderCache::SetShader(g_nativeVertexFmt->m_components);
}


}  // namespace
