#version 400

in vec4 vPosition;
in vec4 vColor;
in int divideByW;
out vec4 color;
uniform mat4 uModelViewMatrix;

void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  gl_Position = (divideByW/gl_Position.w + (1-divideByW)) * gl_Position;
  color = vColor;
}
