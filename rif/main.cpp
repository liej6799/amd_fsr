#include <iostream>
#include "RadeonImageFilters.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#include "ImageTools.h"

#define DEVICE 0
#define BACKEND_TYPE RIF_BACKEND_API_OPENCL

int main() {

    rif_int status = RIF_SUCCESS;
    rif_context context = nullptr;
    rif_command_queue queue = nullptr;
    rif_image_filter filter = nullptr;
    rif_image inputImage = nullptr;
    rif_image outputImage = nullptr;


    // First create context and queue
    int deviceCount = 0;
    status = rifGetDeviceCount(BACKEND_TYPE, &deviceCount);
    if (status != RIF_SUCCESS)
    {
        return -1;
    }
    if (deviceCount > 0 || status)
    {
        status = rifCreateContext(RIF_API_VERSION, BACKEND_TYPE, DEVICE, nullptr, &context);
        if (status != RIF_SUCCESS || !context)
        {
            return -1;
        }
    }
    status = rifContextCreateCommandQueue(context, &queue);
    if (status != RIF_SUCCESS || !queue)
    {
        return -1;
    }

    //Create image filter
    status = rifContextCreateImageFilter(context, RIF_IMAGE_FILTER_GAUSSIAN_BLUR, &filter);
    if (status != RIF_SUCCESS)
    {
        return -1;
    }

    // Load input image
    inputImage = ImageTools::LoadImage("/home/joesl/Development/amd_fsr/rif/images/input.png", context);
    if (!inputImage)
    {
        return -1;
    }

    //Create output image
    rif_image_desc desc;
    size_t retSize;
    rifImageGetInfo(inputImage, RIF_IMAGE_DESC, sizeof(desc), &desc, &retSize);
    status = rifContextCreateImage(context, &desc, nullptr, &outputImage);
    if (status != RIF_SUCCESS)
    {
        return -1;
    }

    //Attach filter and set parameters
    status = rifImageFilterSetParameter1u(filter, "radius", 3);
    if (status != RIF_SUCCESS)
    {
        return -1;
    }
    status = rifImageFilterSetParameter1f(filter, "sigma", 2.0f);
    if (status != RIF_SUCCESS)
    {
        return -1;
    }
    status = rifCommandQueueAttachImageFilter(queue, filter, inputImage, outputImage);
    if (status != RIF_SUCCESS)
    {
        return -1;
    }

    //Execute queue
    status = rifContextExecuteCommandQueue(context, queue, nullptr, nullptr, nullptr);
    if (status != RIF_SUCCESS)
    {
        return -1;
    }

    //Save output image
    ImageTools::SaveImage(outputImage, "out.png");

    //Free resources
    rifCommandQueueDetachImageFilter(queue, filter);
    rifObjectDelete(inputImage);
    rifObjectDelete(outputImage);
    rifObjectDelete(filter);
    rifObjectDelete(queue);
    rifObjectDelete(context);
}
