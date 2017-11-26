#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#define ESCAPE 27

#include "Include.hpp"
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "Model.hpp"
#include "Transformation.hpp"
#include "RealView.hpp"
#include "Frame.hpp"

void frame_capture();

extern GLFWwindow* window;

extern glm::mat4 modelview_matrix;

extern Model model;

extern vector<Character> characters; 

extern vector<int>numframe;
#endif
