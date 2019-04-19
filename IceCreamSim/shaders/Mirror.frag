#version 330


uniform vec3 u_cam_pos;

uniform samplerCube u_texture_cubemap;

in vec4 v_position;
in vec4 v_normal;
in vec4 v_tangent;

out vec4 out_color;

void main() {
//    vec4 i = v_position - vec4(u_cam_pos, 1.0);
//    out_color = reflect(i, v_normal);
    vec4 cam = vec4(u_cam_pos, 0.0);
    vec4 wo = cam * v_position;
    vec4 wi = -wo + 2 * dot(wo, v_normal) * v_normal;
    out_color = texture(u_texture_cubemap, wi.xyz);
  // YOUR CODE HERE
//  out_color = (vec4(1, 1, 1, 0) + v_normal) / 2;
  out_color.a = 1;
}
