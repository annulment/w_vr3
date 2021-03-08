cmake_minimum_required(VERSION 3.8)

project("w_vr3")

set(W_VR3_INLCUDE_FILES  
"include/w_vr3/w_vr3.h"
"include/w_vr3/w_vr3_context.h" 
"include/w_vr3/Window.h" 
"include/w_vr3/debugger.h"
"include/w_vr3/Events.h"
"include/w_vr3/Renderer.h"
)

set(W_VR3_SOURCE_DIR "src/")
set(W_VR3_EXTERNAL_DIR "external/")

add_library(w_vr3 STATIC 
${W_VR3_INLCUDE_FILES}
"${W_VR3_SOURCE_DIR}w_vr3/w_vr3.h"				   "${W_VR3_SOURCE_DIR}w_vr3/w_vr3.cpp" 
"${W_VR3_SOURCE_DIR}w_vr3_context/w_vr3_context.h" "${W_VR3_SOURCE_DIR}w_vr3_context/w_vr3_context.cpp" 
"${W_VR3_SOURCE_DIR}debugger/debugger.h"		   "${W_VR3_SOURCE_DIR}debugger/debugger.cpp"
"${W_VR3_SOURCE_DIR}Window/Window.h"			   "${W_VR3_SOURCE_DIR}Window/Window.cpp"
"${W_VR3_SOURCE_DIR}Events/Events.h" 			   "${W_VR3_SOURCE_DIR}Events/Events.cpp"
"${W_VR3_SOURCE_DIR}OpenGL/Renderer/Renderer.h"    "${W_VR3_SOURCE_DIR}OpenGL/Renderer/Renderer.cpp"
"${W_VR3_SOURCE_DIR}OpenGL/loaders/shader_loader.cpp")

target_include_directories(w_vr3 PUBLIC "include/")

#glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory("${W_VR3_EXTERNAL_DIR}glfw")

#glew
set(glew-cmake_BUILD_SHARED OFF)
add_subdirectory("${W_VR3_EXTERNAL_DIR}glew")

#glm
set(BUILD_STATIC_LIBS ON)
add_subdirectory("${W_VR3_EXTERNAL_DIR}glm")

target_link_libraries(w_vr3 glfw libglew_static glm_static)
