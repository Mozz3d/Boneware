#pragma once

class ModuleProvider
{
public:
    explicit ModuleProvider(HMODULE aHandle)
        : m_handle(aHandle)
    {
        static constexpr uint32_t initialPathSize = 0x200;
        std::wstring pathStr(initialPathSize, L'\0');
        auto pathSize = 0;

        uint8_t attempts = 6;
        while (attempts)
        {
            pathSize = GetModuleFileNameW(aHandle, pathStr.data(), pathStr.size());

            if (pathSize < pathStr.size() - 1) break;

            pathStr.resize(pathStr.size() * 2);

            --attempts;
        }

        if (pathSize > 0)
        {
            pathStr.resize(pathSize);
            m_path = pathStr;
        }
        else
        {
            throw std::runtime_error("Could not resolve module path");
        }
    }

    ~ModuleProvider() = default;

    [[nodiscard]] std::filesystem::path GetPath() const
    {
        return m_path;
    }

    [[nodiscard]] std::filesystem::path GetDirectory() const
    {
        return m_path.parent_path();
    }

    HMODULE m_handle;
    std::filesystem::path m_path;
};