#include "Part.hpp"
using namespace std;

Part::Part(GLuint vPosition, GLuint vColor){
  attrib_pos = vPosition;
  attrib_col = vColor;
  glGenBuffers (1, &vbo);
}

void Part::fromFile(char* inFilename){
  FILE *inpFile = fopen(inFileName, "r");
  glm::vec4 pos(0.0,0.0,0.0,1.0), col(0.0,0.0,0.0,1.0);
  Part* part = new Part;
  
  while(fscanf(inpFile,"%f %f %f %f %f %f",&pos[0],&pos[1],&pos[2],&col[0],&col[1],&col[2])>0){
    part->vertices.push_back(pos);
    part->colors.push_back(col);
  }
  fclose(inpFile);
}

void Part::draw(glm::mat4 Parent_Transformation){
  glBindBuffer (GL_ARRAY_BUFFER,vbo);

    glVertexAttribPointer( attrib_pos, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( attrib_col, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size()*sizeof(glm::vec4)) );
    
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    for(int i=0;i<joints.size();i++){
      joints[i].draw(Parent_Transformation);
    }
}

void Part::addJoint(Joint* joint){
	joints.push_back(joint);
}