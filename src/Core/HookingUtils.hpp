#pragma once

#include <Core/Plugin.hpp>

namespace MidHooking
{
    inline const unsigned char MidShim[] = {
        0x50,                                                 // push rax
        0x51,                                                 // push rcx
        0x52,                                                 // push rdx
        0x53,                                                 // push rbx
        0x55,                                                 // push rbp
        0x56,                                                 // push rsi
        0x57,                                                 // push rdi
        0x41, 0x50,                                           // push r8
        0x41, 0x51,                                           // push r9
        0x41, 0x52,                                           // push r10
        0x41, 0x53,                                           // push r11
        0x41, 0x54,                                           // push r12
        0x41, 0x55,                                           // push r13
        0x41, 0x56,                                           // push r14
        0x41, 0x57,                                           // push r15
        0x9C,                                                 // pushfq

        0x48, 0x81, 0xEC, 0x00, 0x01, 0x00, 0x00,             // sub    rsp, 0x100
        0x0F, 0x11, 0x04, 0x24,                               // movups [rsp+0x00], xmm0
        0x0F, 0x11, 0x4C, 0x24, 0x10,                         // movups [rsp+0x10], xmm1
        0x0F, 0x11, 0x54, 0x24, 0x20,                         // movups [rsp+0x20], xmm2
        0x0F, 0x11, 0x5C, 0x24, 0x30,                         // movups [rsp+0x30], xmm3
        0x0F, 0x11, 0x64, 0x24, 0x40,                         // movups [rsp+0x40], xmm4
        0x0F, 0x11, 0x6C, 0x24, 0x50,                         // movups [rsp+0x50], xmm5
        0x0F, 0x11, 0x74, 0x24, 0x60,                         // movups [rsp+0x60], xmm6
        0x0F, 0x11, 0x7C, 0x24, 0x70,                         // movups [rsp+0x70], xmm7
        0x44, 0x0F, 0x11, 0x84, 0x24, 0x80, 0x00, 0x00, 0x00, // movups [rsp+0x80], xmm8
        0x44, 0x0F, 0x11, 0x8C, 0x24, 0x90, 0x00, 0x00, 0x00, // movups [rsp+0x90], xmm9
        0x44, 0x0F, 0x11, 0x94, 0x24, 0xA0, 0x00, 0x00, 0x00, // movups [rsp+0xA0], xmm10
        0x44, 0x0F, 0x11, 0x9C, 0x24, 0xB0, 0x00, 0x00, 0x00, // movups [rsp+0xB0], xmm11
        0x44, 0x0F, 0x11, 0xA4, 0x24, 0xC0, 0x00, 0x00, 0x00, // movups [rsp+0xC0], xmm12
        0x44, 0x0F, 0x11, 0xAC, 0x24, 0xD0, 0x00, 0x00, 0x00, // movups [rsp+0xD0], xmm13
        0x44, 0x0F, 0x11, 0xB4, 0x24, 0xE0, 0x00, 0x00, 0x00, // movups [rsp+0xE0], xmm14
        0x44, 0x0F, 0x11, 0xBC, 0x24, 0xF0, 0x00, 0x00, 0x00, // movups [rsp+0xF0], xmm15

        0x48, 0x89, 0xE1,                                     // mov    rcx, rsp
        0x48, 0x89, 0xE3,                                     // mov    rbx, rsp
        0x48, 0x83, 0xE4, 0xF0,                               // and    rsp, -16
        0x48, 0x83, 0xEC, 0x20,                               // sub    rsp, 0x20
        0x48, 0xB8,                                           // movabs rax, imm64
        0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,       // Detour ptr
        0xFF, 0xD0,                                           // call   rax
        0x48, 0x89, 0xDC,                                     // mov    rsp, rbx

        0x0F, 0x10, 0x04, 0x24,                               // movups xmm0,  [rsp+0x00]
        0x0F, 0x10, 0x4C, 0x24, 0x10,                         // movups xmm1,  [rsp+0x10]
        0x0F, 0x10, 0x54, 0x24, 0x20,                         // movups xmm2,  [rsp+0x20]
        0x0F, 0x10, 0x5C, 0x24, 0x30,                         // movups xmm3,  [rsp+0x30]
        0x0F, 0x10, 0x64, 0x24, 0x40,                         // movups xmm4,  [rsp+0x40]
        0x0F, 0x10, 0x6C, 0x24, 0x50,                         // movups xmm5,  [rsp+0x50]
        0x0F, 0x10, 0x74, 0x24, 0x60,                         // movups xmm6,  [rsp+0x60]
        0x0F, 0x10, 0x7C, 0x24, 0x70,                         // movups xmm7,  [rsp+0x70]
        0x44, 0x0F, 0x10, 0x84, 0x24, 0x80, 0x00, 0x00, 0x00, // movups xmm8,  [rsp+0x80]
        0x44, 0x0F, 0x10, 0x8C, 0x24, 0x90, 0x00, 0x00, 0x00, // movups xmm9,  [rsp+0x90]
        0x44, 0x0F, 0x10, 0x94, 0x24, 0xA0, 0x00, 0x00, 0x00, // movups xmm10, [rsp+0xA0]
        0x44, 0x0F, 0x10, 0x9C, 0x24, 0xB0, 0x00, 0x00, 0x00, // movups xmm11, [rsp+0xB0]
        0x44, 0x0F, 0x10, 0xA4, 0x24, 0xC0, 0x00, 0x00, 0x00, // movups xmm12, [rsp+0xC0]
        0x44, 0x0F, 0x10, 0xAC, 0x24, 0xD0, 0x00, 0x00, 0x00, // movups xmm13, [rsp+0xD0]
        0x44, 0x0F, 0x10, 0xB4, 0x24, 0xE0, 0x00, 0x00, 0x00, // movups xmm14, [rsp+0xE0]
        0x44, 0x0F, 0x10, 0xBC, 0x24, 0xF0, 0x00, 0x00, 0x00, // movups xmm15, [rsp+0xF0]
        0x48, 0x81, 0xC4, 0x00, 0x01, 0x00, 0x00,             // add rsp, 0x100

        0x9D,                                                 // popfq
        0x41, 0x5F,                                           // pop r15
        0x41, 0x5E,                                           // pop r14
        0x41, 0x5D,                                           // pop r13
        0x41, 0x5C,                                           // pop r12
        0x41, 0x5B,                                           // pop r11
        0x41, 0x5A,                                           // pop r10
        0x41, 0x59,                                           // pop r9
        0x41, 0x58,                                           // pop r8
        0x5F,                                                 // pop rdi
        0x5E,                                                 // pop rsi
        0x5D,                                                 // pop rbp
        0x5B,                                                 // pop rbx
        0x5A,                                                 // pop rdx
        0x59,                                                 // pop rcx
        0x58,                                                 // pop rax

        0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,                   // jmp qword ptr [rip+0]
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,       // Original ptr
    };

    inline constexpr size_t MidShimDetourSlot = 0x9E;
    inline constexpr size_t MidShimOriginalSlot = 0x13F;


    inline bool InstallMidDetour(uintptr_t address, void* detour) {
        const size_t size = sizeof(MidShim);

        void* shim = VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (!shim) return false;
        std::memcpy(shim, MidShim, size);

        std::memcpy(static_cast<uint8_t*>(shim) + MidShimDetourSlot, &detour, sizeof(detour));

        void** originalSlot =
            reinterpret_cast<void**>(static_cast<uint8_t*>(shim) + MidShimOriginalSlot);

        if (!Plugin::RegisterHook(address, shim, originalSlot)) {
            VirtualFree(shim, 0, MEM_RELEASE);
            return false;
        }

        FlushInstructionCache(GetCurrentProcess(), shim, size);
        return true;
    }

    struct MidContext {
        struct Xmm { uint8_t bytes[16]; };

        Xmm      xmm[16];

        uint64_t rflags; // 0x100
        uint64_t r15;    // 0x108
        uint64_t r14;    // 0x110
        uint64_t r13;    // 0x118 
        uint64_t r12;    // 0x120
        uint64_t r11;    // 0x128
        uint64_t r10;    // 0x130
        uint64_t r9;     // 0x138
        uint64_t r8;     // 0x140
        uint64_t rdi;    // 0x148
        uint64_t rsi;    // 0x150 
        uint64_t rbp;    // 0x158
        uint64_t rbx;    // 0x160 
        uint64_t rdx;    // 0x168
        uint64_t rcx;    // 0x170
        uint64_t rax;    // 0x178

        template<typename T>
        T RSP()
        {
            return reinterpret_cast<T>(reinterpret_cast<uintptr_t>(this) + sizeof(MidContext));
        }

        template<typename T>
        T R13()
        {
            return reinterpret_cast<T>(r13);
        }

        template<typename T>
        T RSI()
        {
            return reinterpret_cast<T>(rsi);
        }

        template<typename T>
        T RBX()
        {
            return reinterpret_cast<T>(rbx);
        }

        // other registers
    };

    RED4EXT_ASSERT_SIZE(MidContext, 0x180);
    RED4EXT_ASSERT_OFFSET(MidContext, rflags, 0x100);
    RED4EXT_ASSERT_OFFSET(MidContext, r15, 0x108);
    RED4EXT_ASSERT_OFFSET(MidContext, rdi, 0x148);
    RED4EXT_ASSERT_OFFSET(MidContext, rax, 0x178);
}