#pragma once

namespace util
{
    template <class T>
    void SafeRelease(T** ppT)
    {
        if (*ppT != nullptr)
        {
            (*ppT)->Release();
            *ppT = nullptr;
        }
    }
} // end of namespace util