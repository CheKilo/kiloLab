# 设置 CMake 最低版本要求
cmake_minimum_required(VERSION 3.12)

# 设置项目名称
project(kiloLab_test LANGUAGES CXX)

# 设置构建类型为 Debug
set(CMAKE_BUILD_TYPE "Debug")

# 引入 FetchContent 模块用于下载第三方库
include(FetchContent)
# 声明要下载的 Google Test 库
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        58d77fa8070e8cec2dc1ed015d66b454c8d78850 # release-1.12.1, last version supporting C++11
)
# 使 Google Test 可用
FetchContent_MakeAvailable(googletest)

# 查找 tests 目录下的所有 .cpp 文件作为测试源文件
file(GLOB_RECURSE TEST_SOURCES "*.cpp")

# 定义一个函数来添加测试可执行文件
function(add_kiloLab_test CXX_STANDARD)
    # 生成子项目名称
    set(SUB_PROJECT_NAME "${PROJECT_NAME}_${CXX_STANDARD}")
    # 创建可执行文件
    add_executable(${SUB_PROJECT_NAME} ${TEST_SOURCES})

    # 根据 C++ 标准设置编译选项
    if (CXX_STANDARD EQUAL 11)
        target_compile_options(${SUB_PROJECT_NAME} PRIVATE -std=c++11)
    elseif (CXX_STANDARD EQUAL 14)
        target_compile_options(${SUB_PROJECT_NAME} PRIVATE -std=c++14)
    elseif (CXX_STANDARD EQUAL 17)
        target_compile_options(${SUB_PROJECT_NAME} PRIVATE -std=c++17)
    elseif (CXX_STANDARD EQUAL 20)
        target_compile_options(${SUB_PROJECT_NAME} PRIVATE -std=c++20)
    else ()
        message(FATAL_ERROR "CXX_STANDARD ${CXX_STANDARD} is not available.")
    endif ()

    # 链接 kiloLab 库和 Google Test 库
    target_link_libraries(${SUB_PROJECT_NAME} PRIVATE kiloLab GTest::gtest_main)

    # 引入 Google Test 模块并发现测试
    include(GoogleTest)
    gtest_discover_tests(${SUB_PROJECT_NAME})

    # 设置通用的编译警告选项
    target_compile_options(${SUB_PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endfunction()

# 定义支持的 C++ 标准列表
set(CMAKE_CXX_STANDARD_OPTIONS 11 14 17 20)

# 为每个支持的 C++ 标准添加测试
foreach(CXX_STANDARD ${CMAKE_CXX_STANDARD_OPTIONS})
    add_kiloLab_test(${CXX_STANDARD})
endforeach()