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

#include "CAS_CS.h"

// CAS
#define A_CPU
#include "ffx-cas/ffx_a.h"
#include "ffx-cas/ffx_cas.h"
#include <iostream>
#include <cassert>
#include <vector>

namespace CAS_SAMPLE_VK
{
    void CAS_Filter::OnCreate(VkDevice_T *pDevice) {
        m_pDevice = pDevice;
        {
            VkSamplerCreateInfo info = {};
            info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
            info.magFilter = VK_FILTER_LINEAR;
            info.minFilter = VK_FILTER_LINEAR;
            info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
            info.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            info.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            info.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            info.minLod = -1000;
            info.maxLod = 1000;
            info.maxAnisotropy = 1.0f;
            VkResult res = vkCreateSampler((m_pDevice), &info, NULL, &m_renderSampler);
            assert(res == VK_SUCCESS);
        }

        {
            std::vector<VkDescriptorSetLayoutBinding> layoutBindings(3);
            layoutBindings[0].binding = 0;
            layoutBindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
            layoutBindings[0].descriptorCount = 1;
            layoutBindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
            layoutBindings[0].pImmutableSamplers = NULL;

            layoutBindings[1].binding = 1;
            layoutBindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
            layoutBindings[1].descriptorCount = 1;
            layoutBindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
            layoutBindings[1].pImmutableSamplers = NULL;

            layoutBindings[2].binding = 2;
            layoutBindings[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
            layoutBindings[2].descriptorCount = 1;
            layoutBindings[2].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
            layoutBindings[2].pImmutableSamplers = NULL;

            DefineList defines;
            defines["CAS_SAMPLE_FP16"] = "0";
            defines["CAS_SAMPLE_SHARPEN_ONLY"] = "1";
            m_casSharpenOnly.OnCreate(pDevice, "CAS_Shader.glsl", "main", m_upscaleDescriptorSetLayout, 64, 1, 1, &defines);


        }
    }

    void CAS_Filter::UpdateSharpness(float NewSharpenVal, CAS_State CASState)
    {
        AF1 outWidth = static_cast<AF1>((CASState == CAS_State_Upsample) ? m_width : m_renderWidth);
        AF1 outHeight = static_cast<AF1>((CASState == CAS_State_Upsample) ? m_height : m_renderHeight);

        CasSetup(reinterpret_cast<AU1*>(&m_consts.Const0), reinterpret_cast<AU1*>(&m_consts.Const1), m_sharpenVal, static_cast<AF1>(m_renderWidth),
                 static_cast<AF1>(m_renderHeight), outWidth, outHeight);
        m_sharpenVal = NewSharpenVal;
    }

}