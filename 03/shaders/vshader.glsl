#version 400

in vec4 vPosition;
in vec4 vColor;
in vec2 uv;
out vec2 UV;
out vec4 color;
uniform mat4 uModelViewMatrix;
uniform mat4 uPartMatrix;

void main (void) 
{
  gl_Position = uModelViewMatrix * uPartMatrix * vPosition;
  color = vColor;
  UV = uv;
}
