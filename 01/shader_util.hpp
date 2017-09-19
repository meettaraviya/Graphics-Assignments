#ifndef _SHADER_UTIL_HPP_
#define _SHADER_UTIL_HPP_

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;


namespace csX75
{
  GLuint LoadShaderGL(GLenum eShaderType, const string &strFilename);
  GLuint CreateShaderGL(GLenum eShaderType, const string &strShaderFile);
  GLuint CreateProgramGL(const vector<GLuint> &shaderList);
};

#endif
