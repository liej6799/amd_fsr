cmake_minimum_required(VERSION 3.26)
project(rif)

set(CMAKE_CXX_STANDARD 17)

list(APPEND SAMPLES_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/")
list(APPEND SAMPLES_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/ImageTools/")

list(APPEND SAMPLES_INCLUDE_LIB RadeonImageFilters)

list(APPEND RIF_LIB_PATH "${PROJECT_SOURCE_DIR}/library/Dynamic")

include_directories(${SAMPLES_INCLUDE_DIR})
link_libraries(${SAMPLES_INCLUDE_LIB})
set(SOURCE ${PROJECT_SOURCE_DIR}/main.cpp)
add_executable(rif ${SOURCE})
target_link_directories(rif PRIVATE ${RIF_LIB_PATH})