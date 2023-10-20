// AMD Cauldron code
//
// Copyright(c) 2018 Advanced Micro Devices, Inc.All rights reserved.
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
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

#include <cassert>
#include "PostProcCS.h"

namespace CAULDRON_VK
{

    void PostProcCS::OnCreate(
            VkDevice_T* pDevice,
            const std::string &shaderFilename,
            const std::string &shaderEntryPoint,
            VkDescriptorSetLayout descriptorSetLayout,
            uint32_t dwWidth, uint32_t dwHeight, uint32_t dwDepth,
            DefineList* pUserDefines
    )
    {
        m_pDevice = pDevice;

        VkResult res;

        // Compile shaders
        //
        VkPipelineShaderStageCreateInfo computeShader;
        DefineList defines;
        defines["WIDTH"] = std::to_string(dwWidth);
        defines["HEIGHT"] = std::to_string(dwHeight);
        defines["DEPTH"] = std::to_string(dwDepth);

        if (pUserDefines != NULL)
            defines = *pUserDefines;

        res = VKCompileFromFile(m_pDevice, VK_SHADER_STAGE_COMPUTE_BIT, shaderFilename.c_str(), shaderEntryPoint.c_str(), &defines, &computeShader);
        assert(res == VK_SUCCESS);
    }
}