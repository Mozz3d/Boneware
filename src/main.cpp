#include <rtti.hpp>

RED4EXT_C_EXPORT bool RED4EXT_CALL Main(RED4ext::v1::PluginHandle aHandle, RED4ext::v1::EMainReason aReason, const RED4ext::v1::Sdk* aSdk)
{
    switch (aReason)
    {
    case RED4ext::v1::EMainReason::Load:
    {
        Plugin::Init(aHandle, aSdk);
        Plugin::RegisterScriptsDirectory(Plugin::ResolveModulePath().parent_path() / "scripts");
        // FIXME: this sucks, need to improve hooking semantics
        Plugin::AttachHook(
            NativeInfo<RED4ext::ent::ISkinTargetComponent>::OnTransformUpdated::Addr,
            &ISkinTargetComponent_OnTransformUpdated
        );

        break;
    }
    case RED4ext::v1::EMainReason::Unload:
    {
        // TODO: Deinit plugin?
        break;
    }
    }

    return true;
}

RED4EXT_C_EXPORT void RED4EXT_CALL Query(RED4ext::v1::PluginInfo* aInfo)
{
    aInfo->name = L"Boneware";
    aInfo->author = L"Mozz";
    aInfo->version = RED4EXT_V1_SEMVER(0, 0, 3);
    aInfo->runtime = RED4EXT_V1_RUNTIME_VERSION_LATEST;
    aInfo->sdk = RED4EXT_V1_SDK_VERSION_CURRENT;
}

RED4EXT_C_EXPORT uint32_t RED4EXT_CALL Supports()
{
    return RED4EXT_API_VERSION_1;
}
