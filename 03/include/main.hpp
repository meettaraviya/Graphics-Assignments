#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#define ESCAPE 27

#include "Include.hpp"
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "Scene.hpp"
#include "Transformation.hpp"
#include "RealView.hpp"

extern GLFWwindow* window;

extern GLuint shaderProgram, vPosition, vColor, uModelViewMatrix;

extern glm::mat4 modelview_matrix;

extern Scene scene;
extern PointArray viewEye;
extern LineArray viewFrustum, viewAxes;


#endif
