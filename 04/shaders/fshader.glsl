#version 400

in vec4 color;
in vec2 UV;
out vec4 frag_color;
uniform sampler2D t_sampler;
uniform vec4 isTextured;


void main ()
{
  // if(isTextured[0]>0.5){
	frag_color = texture( t_sampler, UV ).rgba;
  // }else{
  	// frag_color = color;
  // }
}
