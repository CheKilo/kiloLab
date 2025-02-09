# 设置 CMake 最低版本要求
cmake_minimum_required(VERSION 3.12)

# 设置项目名称和使用的语言
project(kiloLab LANGUAGES CXX)

# 要求编译器必须支持指定的 C++ 标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 如果没有指定构建类型，默认设置为 Debug
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose build type: Debug/Release/RelWithDebInfo/MinSizeRel." FORCE)
endif ()

# 设置 FetchContent 下载第三方库的存储目录
set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party")

# 定义是否构建单元测试的选项
option(KILOLAB_BUILD_TESTS "Build unit tests" ${PROJECT_IS_TOP_LEVEL})

# 创建一个接口库
add_library(kiloLab INTERFACE)

# 设置库的包含目录，使用 INTERFACE 意味着使用该库的目标会包含此目录
target_include_directories(kiloLab INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 不需要添加源文件，因为是接口库

# 如果选择构建单元测试
if (KILOLAB_BUILD_TESTS)
    # 启用 CMake 的测试功能
    enable_testing()
    # 处理 test 子目录中的 CMakeLists.txt 文件
    add_subdirectory(test)
endif ()