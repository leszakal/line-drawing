# CMakeList.txt : CMake project for algo_project, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("algo_project")

# Source files
set(SOURCES 
	src/main.cpp 
	src/bresenham.cpp 
	src/xiaolin_wu.cpp
	src/render.cpp
	src/menu.cpp
	include/bresenham.h
	include/point.h
	include/xiaolin_wu.h
	include/render.h
	include/menu.h
)

# Add source to this project's executable.
add_executable(algo_project ${SOURCES})

# Include header files
target_include_directories(algo_project PRIVATE include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET algo_project PROPERTY CXX_STANDARD 20)
endif()

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.2.10
)
FetchContent_MakeAvailable(SDL3)

# Link SDL3
target_link_libraries(algo_project PRIVATE SDL3::SDL3)

# Move .dll files to output directory
# https://stackoverflow.com/questions/10671916/how-to-copy-dll-files-into-the-same-folder-as-the-executable-using-cmake
add_custom_command(TARGET algo_project POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3::SDL3>
    $<TARGET_FILE_DIR:algo_project>
)
