cmake_minimum_required( VERSION 3.5 )

set(PROJECT_NAME, "opengltest")
project( opengltest)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenGL_GL_PREFERENCE LEGACY)
find_package( OpenGL REQUIRED )
find_package(GLEW REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} )

add_subdirectory(glm/glm-master)
# target_link_libraries(${PROJECT_NAME} glm::glm)
# target_include_directories(${PROJECT_NAME} glm/glm-master)

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
# set( GLAD_GL "" )

add_subdirectory( glfw )
include_directories(include/external)
include_directories(${GLFW_SOURCE_DIR}/src)


add_subdirectory(assimp)
include_directories(${PROJECT_SOURCE_DIR}/assimp/include)
# option( GLFW-CMAKE-STARTER-USE-GLFW-GLAD "Use GLAD from GLFW" OFF )

# if( GLFW-CMAKE-STARTER-USE-GLFW-GLAD )
#     include_directories("${GLFW_SOURCE_DIR}/deps")
#     # set( GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/glad.h" )
# else()
#     include_directories(${PROJECT_SOURCE_DIR}/glad/include)
#     set( GLAD_GL "${PROJECT_SOURCE_DIR}/glad/include/glad/glad.h")
# endif()

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/GL
)

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        # glad/src/glad.c
        )

add_executable( ${PROJECT_NAME} WIN32 ${all_SRCS} )
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Wpedantic -g -O0 -ggdb -fno-omit-frame-pointer -gcolumn-info)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/assimp/build/bin/libassimp.so)
target_link_libraries( ${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw GLEW::glew)
if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set '${PROJECT_NAME}' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )
    endif()
endif()
