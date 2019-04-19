#version 330

uniform vec4 u_color;
uniform vec3 u_cam_pos;
uniform vec3 u_light_pos;
uniform vec3 u_light_intensity;

in vec4 v_position;
in vec4 v_normal;
in vec2 v_uv;

out vec4 out_color;

void main() {
  // YOUR CODE HERE
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
    vec4 n = normalize(v_normal);
    float dotNL = dot(n, l);

    vec4 v = vec4(u_cam_pos, 1.0) - v_position;
    v = normalize(v);
    vec4 h = v + l;
    h = normalize(h);
    float dotNH = dot(n, h);
    
    vec3 x_y_z = (ka * ia) + (kd * i_r2 * max(0.0, dotNL)) + (ks * i_r2 * pow(max(0.0, dotNH), p));
    out_color.xyz = x_y_z;
  
  // (Placeholder code. You will want to replace it.)
  out_color.a = 1;
}

