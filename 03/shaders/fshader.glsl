#version 400

in vec4 color;
in vec2 UV;
out vec4 frag_color;
uniform sampler2D t_sampler;


void main ()
{
  // frag_color = vec4(UV[0],UV[1],0,1);
  frag_color = texture( t_sampler, UV ).rgba;
  // frag_color = vec4(UV,0.0, 1.0);
  // vec3 c = texture( t_sampler, vec2(0,0.5) ).rgb;
  // frag_color = vec4(c[0], c[1], c[2], 1.0);
  // frag_color = vec4(color[0], UV[1], UV[0], 0.0);
  // frag_color = color;
}
