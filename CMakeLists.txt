﻿# CMakeList.txt : CMake project for TileExtractor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
#set( CMAKE_TOOLCHAIN_FILE "C:/Program Files/Microsoft Visual Studio/2022/Enterprise/VC/vcpkg/scripts/buildsystems/vcpkg.cmake" )

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("TileExtractor")

# Add source to this project's executable.
add_executable (TileExtractor "TileExtractor.cpp" "TileExtractor.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TileExtractor PROPERTY CXX_STANDARD 20)
endif()

find_package(OpenCV CONFIG REQUIRED)
target_link_libraries(TileExtractor PRIVATE ${OpenCV_LIBS})

# TODO: Add tests and install targets if needed.
