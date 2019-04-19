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
    float ka = 0.1;
    float kd = 1.0;
    float ks = 0.5;
    vec3 ia = vec3(1.0, 1.0, 1.0);
    
    float p = 200.0;
    
    vec3 n_lightIntensity = normalize(u_light_intensity);
    vec3 n_lightPos = normalize(u_light_pos);
    vec3 n_camPos = normalize(u_cam_pos);
    vec3 n_normal = normalize(vec3(v_normal));
    vec3 pos3 = vec3(v_position);
    
    //create l and v to find h
    vec3 l = normalize(u_light_pos - pos3);
    vec3 v = normalize(u_cam_pos - pos3);
    
    //calculate h from l and v like in the slides
    vec3 h = normalize(l + v);
    
    // (Placeholder code. You will want to replace it.)
    //combo
    out_color = vec4(((ka * ia) + (kd * n_lightIntensity * max(0, dot(n_normal, l))) + (ks * n_lightIntensity * pow(max(0, dot(n_normal, h)), p))), 1.0);
    //just ambient
    //out_color = vec4((ka * ia), 1.0);
    //just diffuse
    //out_color = vec4((kd * n_lightIntensity * max(0, dot(n_normal, l))), 1.0);
    //just specular
    //out_color = vec4((ks * n_lightIntensity * pow(max(0, dot(n_normal, h)), p)), 1.0);
    out_color *= u_color;
    out_color.a = 1;
}

