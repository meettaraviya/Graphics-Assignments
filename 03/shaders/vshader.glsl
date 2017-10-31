#version 400

in vec4 vPosition;
in vec4 vColor;
in vec2 uv;
out vec4 color;
uniform mat4 uModelViewMatrix;

void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  color = vColor;
}
