#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coord;
layout (location = 3) in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 v_color;
out vec2 v_tex_coord;
out vec3 v_normal;
out vec3 v_frag_position;


void main() {
    gl_Position = projection * view * model * vec4(position, 1);

    v_color = color;
    v_tex_coord = tex_coord;
    v_normal = mat3(transpose(inverse(model))) * normal;
    v_frag_position = vec3(model * vec4(position, 1));   // multiply with view matrix?
}