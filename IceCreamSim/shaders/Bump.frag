#version 330

uniform vec3 u_cam_pos;
uniform vec3 u_light_pos;
uniform vec3 u_light_intensity;

uniform vec4 u_color;

uniform sampler2D u_texture_2;
uniform vec2 u_texture_2_size;

uniform float u_normal_scaling;
uniform float u_height_scaling;

in vec4 v_position;
in vec4 v_normal;
in vec4 v_tangent;
in vec2 v_uv;

out vec4 out_color;

float h(vec2 uv) {
  //as suggested, get the r component of the
    //texture color vector stored at (u, v)
  return texture(u_texture_2, uv).r;
}

void main() {
  // YOUR CODE HERE
    //find b from n and t (cross product)
    vec3 n3 = vec3(v_normal);
    vec3 t3 = vec3(v_tangent);
    vec3 b = cross(n3, t3);
    
    //find TBN
    mat3 tbn = mat3(t3, b, n3);
    
    //get u and v for calculation of dU and dV
    float u = v_uv[0];
    float v = v_uv[1];
    
    //uH calc
    float uH = h(vec2(u + 1/u_texture_2_size[0], v));
    float vH = h(vec2(u, v + 1/u_texture_2_size[1]));
    
    float kh = u_height_scaling;
    float kn = u_normal_scaling;
    
    //dU
    float dU = (uH - h(v_uv)) * kh * kn;
    
    //dV
    float dV = (vH - h(v_uv)) * kh * kn;
    
    //local space normal calculation
    vec3 no = vec3(-1 * dU, -1 * dV, 1.0);
    
    //displaced normal calculation
    vec3 nd = tbn * no;
    
    //shading code
    float ka = 0.1;
    float kd = 1.0;
    float ks = 0.5;
    vec3 ia = vec3(1.0, 1.0, 1.0);
    
    float p = 200.0;
    
    vec3 n_lightIntensity = normalize(u_light_intensity);
    vec3 n_lightPos = normalize(u_light_pos);
    vec3 n_camPos = normalize(u_cam_pos);
    vec3 n_normal = normalize(nd);
    vec3 pos3 = vec3(v_position);
    
    //create l and v to find h
    vec3 l = normalize(u_light_pos - pos3);
    vec3 v2 = normalize(u_cam_pos - pos3);
    
    //calculate h from l and v like in the slides
    vec3 h = normalize(l + v2);
    
    // (Placeholder code. You will want to replace it.)
    out_color = vec4(((ka * ia) + (kd * n_lightIntensity * max(0, dot(n_normal, l))) + (ks * n_lightIntensity * pow(max(0, dot(n_normal, h)), p))), 1.0);
    out_color *= u_color;
    out_color.a = 1;
    
    //rad bump cloth look
  //find b from n and t (cross product)
//    vec3 n3 = vec3(v_normal);
//    vec3 t3 = vec3(v_tangent);
//    vec3 b = cross(n3, t3);
//
//    //find TBN
//    mat3 tbn = mat3(t3, b, n3);
//
//    //get u and v for calculation of dU and dV
//    float u = v_uv[0];
//    float v = v_uv[1];
//
//    //uH calc
//    float uH = h(vec2((u + 1)/u_texture_2_size[0], v));
//    float vH = h(vec2(u, (v + 1)/u_texture_2_size[1]));
//
//    float kh = u_height_scaling;
//    float kn = u_normal_scaling;
//
//    //dU
//    float dU = (uH - h(v_uv)) * kh * kn;
//
//    //dV
//    float dV = (vH - h(v_uv)) * kh * kn;
//
//    //local space normal calculation
//    vec3 no = vec3(-1.0 * dU, -1.0 * dV, 1.0);
//
//    //displaced normal calculation
//    vec3 nd = tbn * no;
//
//    //shading code
//    float ka = 0.1;
//    float kd = 1.0;
//    float ks = 0.5;
//    vec3 ia = vec3(1.0, 1.0, 1.0);
//
//    float p = 200.0;
//
//    vec3 n_lightIntensity = normalize(u_light_intensity);
//    vec3 n_lightPos = normalize(u_light_pos);
//    vec3 n_camPos = normalize(u_cam_pos);
//    vec3 n_normal = normalize(nd);
//    vec3 pos3 = vec3(v_position);
//
//    //create l and v to find h
//    vec3 l = normalize(u_light_pos - pos3);
//    vec3 v2 = normalize(u_cam_pos - pos3);
//
//    //calculate h from l and v like in the slides
//    vec3 h = normalize(l + v2);
//
//    // (Placeholder code. You will want to replace it.)
//    out_color = vec4(((ka * ia) + (kd * n_lightIntensity * max(0, dot(n_normal, l))) + (ks * n_lightIntensity * pow(max(0, dot(n_normal, h)), p))), 1.0);
//    out_color *= u_color;
//    out_color.a = 1;
}

