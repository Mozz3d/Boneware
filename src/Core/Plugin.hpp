#pragma once

#include <RED4ext/Api/v1/PluginHandle.hpp>
#include <RED4ext/Api/v1/Sdk.hpp>

class Plugin
{
public:
	static Plugin& Init(
		RED4ext::v1::PluginHandle aHandle, 
		const RED4ext::v1::Sdk* aSDK
	)
	{
		static Plugin instance(aHandle, aSDK);
		s_instance = &instance;
		Red::TypeInfoRegistrar::RegisterDiscovered();
		return instance;
	}

	Plugin(const Plugin&) = delete;
	Plugin& operator=(const Plugin&) = delete;
	Plugin(Plugin&&) = delete;
	Plugin& operator=(Plugin&&) = delete;

	[[nodiscard]] static const std::filesystem::path ResolveModulePath()
	{
		std::wstring path(MAX_PATH, L'\0');

		auto pathSize = GetModuleFileNameW(s_instance->m_handle, path.data(), path.size());
		if (pathSize == 0)
		{
			throw std::runtime_error("Could not resolve module path");
		}

		path.resize(pathSize);
		return std::move(path);
	}

	static void RegisterScriptsDirectory(const std::filesystem::path& aDirectory)
	{
		s_instance->m_api->scripts->Add(s_instance->m_handle, aDirectory.c_str());
	}

	static bool AttachHook(uintptr_t aTarget, void* aCallback, void** aOriginal = nullptr)
	{
		return s_instance->m_api->hooking->Attach(s_instance->m_handle, reinterpret_cast<void*>(aTarget), aCallback, aOriginal);
	}

	static bool DetachHook(void* aTarget)
	{
		return s_instance->m_api->hooking->Detach(s_instance->m_handle, aTarget);
	}

private:
	static inline Plugin* s_instance = nullptr;

	Plugin( 
		const RED4ext::v1::PluginHandle aHandle, 
		const RED4ext::v1::Sdk* aAPI
	)
		: m_handle(aHandle), m_api(aAPI)
	{
	}

	const RED4ext::v1::PluginHandle m_handle;
	const RED4ext::v1::Sdk* m_api;
};

