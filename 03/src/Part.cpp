#include "Part.hpp"
using namespace std;

Part::Part(GLuint vPosition, GLuint vColor){
  attrib_pos = vPosition;
  attrib_col = vColor;
  glGenBuffers (1, &vbo);
}

void Part::draw(glm::mat4 Parent_Transformation){
  glBindBuffer (GL_ARRAY_BUFFER,vbo);

    glVertexAttribPointer( attrib_pos, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( attrib_col, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size()*sizeof(glm::vec4)) );
    
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

void Part::addJoint(Joint* joint){
	joints.push_back(joint);
}
