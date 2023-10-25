#include <iostream>
#include "RadeonImageFilters.h"


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
    std::cout << status << std::endl;
    if (status != RIF_SUCCESS)
    {
        return -1;
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
