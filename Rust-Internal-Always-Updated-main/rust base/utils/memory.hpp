#pragma once
#include "../includes.hpp"

namespace memory
{
    uintptr_t sigscan(const char* module, const char* pattern, int jump = 0);
    uintptr_t find(uintptr_t range_start, uintptr_t range_end, const char* pattern);
    uintptr_t find(const char* mod, const char* pattern);

    uintptr_t find_rel(const char* mod, const char* pattern, ptrdiff_t position = 0, ptrdiff_t jmp_size = 3, ptrdiff_t instruction_size = 7);

    template<typename t = uintptr_t>
    t read(uintptr_t address)
    {
        if (!address)
        {
            return t();
        }
        else if (address < 0xffffff)
        {
            return t();
        }
        else if (address > 0x7fffffff0000)
        {
            return t();
        }
        else
        {
            return *reinterpret_cast<t*>(address);
        }
    }

    template<typename t>
    bool write(uintptr_t address, t value)
    {
        *reinterpret_cast<t*>(address) = value;
        return true;
    }
}