#pragma once

#include <RED4ext/Rendering/RenderObject.hpp>

struct IRenderSkinningData : RED4ext::IRenderObject
{
	virtual uint32_t GetMatrixCount() const = 0;
};
