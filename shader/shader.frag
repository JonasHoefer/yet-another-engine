#version 330 core
#define SPOT_LIGHT_COUNT 2
#define POINT_LIGHT_COUNT 1

struct material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct point_light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct directional_light {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct spot_light {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutoff_angle;
    float outer_cutoff_angle;
};


layout (location = 0) out vec4 color;

uniform vec3 u_view_position;
uniform material u_material;
uniform point_light u_point_lights[POINT_LIGHT_COUNT];
uniform directional_light u_directional_light;
uniform spot_light u_spot_lights[SPOT_LIGHT_COUNT];

in vec3 v_color;
in vec2 v_tex_coord;
in vec3 v_normal;
in vec3 v_frag_position;


vec3 calculate_directional_light(directional_light light, vec3 normal, vec3 view_direction) {
    // ambient
    vec3 ambient = light.ambient * vec3(texture(u_material.diffuse, v_tex_coord));

    // diffuse
    vec3 light_direction = normalize(-light.direction);
    float diff = max(dot(normal, light_direction), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(u_material.diffuse, v_tex_coord));

    // specular
    vec3 reflect_direction = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), u_material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(u_material.specular, v_tex_coord));

    // emission
    vec3 emission = vec3(texture(u_material.emission, v_tex_coord));

    // adding
    return ambient + diffuse + specular + emission;
}

vec3 calculate_point_light(point_light light, vec3 normal, vec3 view_direction) {
    // ambient
    vec3 ambient = light.ambient * vec3(texture(u_material.diffuse, v_tex_coord));

    // diffuse
    vec3 light_direction = normalize(light.position - v_frag_position);
    float diff = max(dot(normal, light_direction), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(u_material.diffuse, v_tex_coord));

    // specular
    vec3 reflect_direction = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), u_material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(u_material.specular, v_tex_coord));

    // emission
    vec3 emission = vec3(texture(u_material.emission, v_tex_coord));


    // calculations for attentution
    float distance = length(light.position - v_frag_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // include attenuation
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // adding
    return ambient + diffuse + specular + emission;
}

vec3 calculate_spot_light(spot_light light, vec3 normal, vec3 view_direction) {
    // ambient
    vec3 ambient = light.ambient * vec3(texture(u_material.diffuse, v_tex_coord));

    // diffuse
    vec3 light_direction = normalize(light.position - v_frag_position);
    float diff = max(dot(normal, light_direction), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(u_material.diffuse, v_tex_coord));

    // specular
    vec3 reflect_direction = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), u_material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(u_material.specular, v_tex_coord));

    // emission
    vec3 emission = vec3(texture(u_material.emission, v_tex_coord));

    // spotlight
    float theta = dot(light_direction, normalize(-light.direction));
    float epsilon = light.cutoff_angle - light.outer_cutoff_angle;
    float intensity = clamp((theta - light.outer_cutoff_angle) / epsilon, 0.0, 1.0);

    diffuse *= intensity;
    specular *= intensity;

    // adding
    return ambient + diffuse + specular;
}

void main() {
    vec3 normal = normalize(v_normal);
    vec3 view_direction = normalize(u_view_position - v_frag_position);


    vec3 result = vec3(0, 0, 0);
    result += calculate_directional_light(u_directional_light, normal, view_direction);

    for (int i = 0;i < POINT_LIGHT_COUNT;++i)
        result += calculate_point_light(u_point_lights[i], normal, view_direction);

    for (int i = 0;i < SPOT_LIGHT_COUNT;++i)
        result += calculate_spot_light(u_spot_lights[i], normal, view_direction);

    color = vec4(result, 1.0);
}