#version 330

uniform vec3 u_cam_pos;
uniform vec3 u_light_pos;
uniform vec3 u_light_intensity;

uniform vec4 u_color;

uniform sampler2D u_texture_3;
uniform vec2 u_texture_3_size;

uniform float u_normal_scaling;
uniform float u_height_scaling;

in vec4 v_position;
in vec4 v_normal;
in vec4 v_tangent;
in vec2 v_uv;

out vec4 out_color;

float h(vec2 uv) {
  // You may want to use this helper function...
    vec4 tex = texture(u_texture_3, uv);
    float r = tex.r;
    return r;
}

void main() {
  // YOUR CODE HERE
    vec4 n = v_normal;
    vec4 t = v_tangent;
    vec3 b = cross(t.xyz, n.xyz);
    mat3 tbn = mat3(t.xyz, b, n.xyz);
    
    float u = v_uv.x;
    float v_coord = v_uv.y;
    float w = u_texture_3_size.x;
    float height = u_texture_3_size.y;
    
    vec2 uv1 = vec2(u + (1.0/w), v_coord);
    vec2 uv2 = vec2(u, v_coord + (1.0/height));
    
    float du = ( h(uv1) - h(v_uv) ) * u_height_scaling * u_normal_scaling;
    float dv = (h(uv2) - h(v_uv)) * u_height_scaling * u_normal_scaling;
    
    vec3 nO = vec3((du * -1.0), (dv * -1.0), 1.0);
    vec3 nd = tbn * nO;
    
    
    
    
    
    float ka = 0.01;
    vec3 ia = vec3(0.25, 0.25, 0.25);
    float kd = 1.0;
    float ks = 0.5;
    float p = 100.0;
    
    vec3 i = u_light_intensity;
    float r = distance(vec4(u_light_pos, 1.0), v_position);
    vec3 i_r2 = i / (r * r);
    
    vec4 l = vec4(u_light_pos, 1.0) - v_position;
    l = normalize(l);
    vec4 newN = vec4(nd, 1.0);
//    newN = normalize(newN);
    float dotNL = dot(newN, l);
    
    vec4 v = vec4(u_cam_pos, 1.0) - v_position;
    v = normalize(v);
    vec4 h_phong = v + l;
    h_phong = normalize(h_phong);
    float dotNH = dot(newN, h_phong);
    
    vec3 x_y_z = (ka * ia) + (kd * i_r2 * max(0.0, dotNL)) + (ks * i_r2 * pow(max(0.0, dotNH), p));
    out_color.xyz = x_y_z;
    out_color.a = 1;

}

