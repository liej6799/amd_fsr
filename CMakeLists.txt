cmake_minimum_required(VERSION 3.26)
project(amd_fsr)

set(CMAKE_CXX_STANDARD 23)

add_executable(amd_fsr main.cpp
        VulkanExample.cpp
        VulkanExample.h
        VulkanTools.cpp
        VulkanTools.h
        ffx-cas/ffx_a.h
        ffx-cas/ffx_cas.h
        CAS_CS.cpp
        CAS_CS.h
        PostProcCS.cpp
        PostProcCS.h
        ShaderCompiler.cpp
        ShaderCompiler.h
        Hash.cpp
        Hash.h
        Misc.cpp
        Misc.h
        ShaderCompilerHelper.cpp
        ShaderCompilerHelper.h
        ThreadPool.cpp
        ThreadPool.h
        AsyncCache.h
        Async.cpp
        Async.h)

find_package(Vulkan REQUIRED)

add_subdirectory(libs/vectormath)

target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
