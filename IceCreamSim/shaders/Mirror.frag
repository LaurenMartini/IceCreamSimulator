#version 330


uniform vec3 u_cam_pos;

uniform samplerCube u_texture_cubemap;

in vec4 v_position;
in vec4 v_normal;
in vec4 v_tangent;

out vec4 out_color;

void main() {
  // YOUR CODE HERE
    //compute wo from u_cam_pos and v_position
    vec3 p3 = vec3(v_position);
    vec3 wo = p3 - u_cam_pos;
    
    //reflect wo across the surface normal given v_normal
    //this gives wi
    vec3 n3 = vec3(v_normal);
    vec3 wi = reflect(wo, n3);
    
    //sample environment map u_texture_cubemap for the
    //incoming direction wi
    vec4 sampleMap = texture(u_texture_cubemap, wi);
    out_color = sampleMap;
//  out_color = (vec4(1, 1, 1, 0) + v_normal) / 2;
//  out_color.a = 1;
}
