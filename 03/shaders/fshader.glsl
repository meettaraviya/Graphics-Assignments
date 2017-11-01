#version 400

in vec4 color;
in vec2 UV;
out vec4 frag_color;
uniform sampler2D t_sampler;
uniform int isTextured;


void main ()
{
  // frag_color = vec4(UV[0],UV[1],0,1);
  if(isTextured>0){
	frag_color = texture( t_sampler, UV ).rgba;
  }else{
  	frag_color = color;
  }
}
