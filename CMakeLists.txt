cmake_minimum_required(VERSION 3.9)
project(yet_another_engine)

set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE LEGACY) # use legacy OpenGL since only it will be available on windows

find_library(GLEW REQUIRED STATIC)
find_library(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)


include_directories(include dependencies/stb_image/include dependencies/tiny_obj_loader ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})


link_libraries(${GLFW3_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

set(SOURCE_FILES include/yae/gl/buffer.hpp include/yae/gl/error_utils.hpp include/yae/gl/index_buffer.hpp include/yae/gl/shader.hpp include/yae/gl/shader_program.hpp include/yae/gl/texture.hpp include/yae/gl/type_utils.h include/yae/gl/vertex_array.hpp include/yae/pil/file_utils.hpp include/yae/pil/string_utils.hpp include/yae/utils/counter.hpp include/yae/vertex.hpp include/yae/window.hpp src/index_buffer.cpp src/shader.cpp src/shader_program.cpp src/texture.cpp src/vertex_array.cpp src/window.cpp include/yae/directional_light.hpp include/yae/material.hpp src/material.cpp include/yae/mesh.hpp src/mesh.cpp src/vertex.cpp src/directional_light.cpp src/point_light.cpp include/yae/point_light.hpp include/yae/spot_light.hpp src/spot_light.cpp include/yae/gl/cube_map.hpp src/cube_map.cpp include/yae/skybox.hpp src/skybox.cpp include/yae/math/matrix.hpp include/yae/math/quaternion.hpp include/yae/math/transform.hpp)

add_executable(model ${SOURCE_FILES} test/model_test.cpp)
add_executable(math_test ${SOURCE_FILES} test/math_test.cpp)

target_link_libraries(model GLEW glfw)
target_link_libraries(math_test GLEW glfw)