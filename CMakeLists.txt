cmake_minimum_required(VERSION 3.12)
project(winerosetta)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_library(winerosetta SHARED src/winerosetta.cpp src/winerosetta.def)

project(winerosettaldr)
add_executable(winerosettaldr WIN32 src/loader.cpp)

set_target_properties(winerosetta PROPERTIES PREFIX "")  # Add this line

if(MINGW)
  # Check if we're using Clang
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # For Clang with MinGW, explicitly specify static linking of C++ runtime
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc -static-libstdc++")
  else()
    # For regular MinGW/GCC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++")
  endif()
  
  # Disable libunwind
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-unwind-tables")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fno-unwind-tables -fno-exceptions")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fno-unwind-tables -fno-exceptions")
  
  # Static linking for the loader executable
  target_link_options(winerosettaldr PRIVATE -static)
endif()