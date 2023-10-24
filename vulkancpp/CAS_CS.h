//CAS Sample
//
// Copyright(c) 2019 Advanced Micro Devices, Inc.All rights reserved.
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include <cstdint>
#include <vulkan/vulkan.h>
#include "PostProcCS.h"

#if (__cplusplus >= 202002L)
#include <compare>
#endif

namespace CAS_SAMPLE_VK
{
    // https://github.com/microsoft/DirectXMath/blob/main/Inc/DirectXMath.h
    // 4D Vector; 32 bit unsigned integer components
    struct XMUINT4
    {
        uint32_t x;
        uint32_t y;
        uint32_t z;
        uint32_t w;

        XMUINT4() = default;

        XMUINT4(const XMUINT4&) = default;
        XMUINT4& operator=(const XMUINT4&) = default;

        XMUINT4(XMUINT4&&) = default;
        XMUINT4& operator=(XMUINT4&&) = default;

        constexpr XMUINT4(uint32_t _x, uint32_t _y, uint32_t _z, uint32_t _w) noexcept : x(_x), y(_y), z(_z), w(_w) {}
        // XMUINT4(_In_reads_(4) const uint32_t* pArray) noexcept : x(pArray[0]), y(pArray[1]), z(pArray[2]), w(pArray[3]) {}

        #if (__cplusplus >= 202002L)
                bool operator == (const XMUINT4&) const = default;
                auto operator <=> (const XMUINT4&) const = default;
        #endif
    };

    enum CAS_State
    {
        CAS_State_NoCas,
        CAS_State_Upsample,
        CAS_State_SharpenOnly,
    };

    struct ResolutionInfo
    {
        const char* pName;
        uint32_t Width;
        uint32_t Height;
    };

    struct CASConstants
    {
        XMUINT4 Const0;
        XMUINT4 Const1;
    };

    class CAS_Filter
    {
    public:
        void OnCreate(VkDevice_T* pDevice);

        void UpdateSharpness(float NewSharpen, CAS_State CASState);

    private:
        VkDevice_T *m_pDevice;
        float                           m_sharpenVal;
        uint32_t                        m_renderWidth;
        uint32_t                        m_renderHeight;
        uint32_t                        m_width;
        uint32_t                        m_height;
        CASConstants                    m_consts;

        CAULDRON_VK::PostProcCS         m_casSharpenOnly;

        VkImageView                     m_dstTextureSRV;
        VkSampler                       m_renderSampler; // Samples dst texture for rendering to swap chain

        VkDescriptorSet                 m_upscaleDescriptorSet;
        VkDescriptorSetLayout           m_upscaleDescriptorSetLayout;

        VkDescriptorSet                 m_renderDstSRVDescriptorSet;
        VkDescriptorSet                 m_renderSrcSRVDescriptorSet;
        VkDescriptorSetLayout           m_renderDescriptorSetLayout;

        bool                            m_dstLayoutUndefined;
    };
}
