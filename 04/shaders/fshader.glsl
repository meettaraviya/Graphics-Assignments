#version 400

in vec4 color;
in vec2 UV;
out vec4 frag_color;
uniform sampler2D t_sampler;
uniform bool isTextured;


void main ()
{
  if(isTextured){
	frag_color = texture( t_sampler, UV ).rgba;
  }else{
  	frag_color = color;
  }
}
