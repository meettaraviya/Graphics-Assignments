#ifndef _INCLUDE_HPP_
#define _INCLUDE_HPP_

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

#define TPF 1.0/6000

// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))
#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 512

#define GRID_N 32
#define GRID_M 48

#define PLAYBACK 0
#define RECORD 1
#define RENDER 2

using namespace std;

extern const glm::mat4 id;
extern GLuint shaderProgram, vPosition, vColor, vUV, uModelViewMatrix, vIsTextured;

extern int mode;

#endif