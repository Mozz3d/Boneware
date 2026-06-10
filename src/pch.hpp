#pragma once

#define RED4EXT_HEADER_ONLY

#include <iostream>
#include <filesystem>
#include <functional>

#include <windows.h>

#include <RED4ext.hpp>
#include <RedLib.hpp>

#include <RTTITypes.hpp>
#include <Relocation.hpp>
#include <Callback.hpp>

#include <Core/MacroUtils.hpp>
#include <Core/Plugin.hpp>
#include <Core/PtrUtils.hpp>
#include <Core/NativeInfoUtils.hpp>

#include <Containers/Span.hpp>

#include <Memory/Allocators.hpp>
#include <Memory/UniquePtr.hpp>

#include <Scripting/Natives/animRig.hpp>
#include <Scripting/Natives/Vector4.hpp>
#include <Scripting/Natives/Generated/QsTransform.hpp>
#include <Scripting/Natives/Generated/WorldTransform.hpp>
#include <Lib/VectorMath.hpp>
#include <Lib/ScriptedUtils.hpp>
