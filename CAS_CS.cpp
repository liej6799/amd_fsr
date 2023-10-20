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

namespace CAS_SAMPLE_VK
{
    void CAS_Filter::UpdateSharpness(float NewSharpenVal, CAS_State CASState)
    {
        AF1 outWidth = static_cast<AF1>((CASState == CAS_State_Upsample) ? m_width : m_renderWidth);
        AF1 outHeight = static_cast<AF1>((CASState == CAS_State_Upsample) ? m_height : m_renderHeight);

        CasSetup(reinterpret_cast<AU1*>(&m_consts.Const0), reinterpret_cast<AU1*>(&m_consts.Const1), m_sharpenVal, static_cast<AF1>(m_renderWidth),
                 static_cast<AF1>(m_renderHeight), outWidth, outHeight);
        m_sharpenVal = NewSharpenVal;
    }
}