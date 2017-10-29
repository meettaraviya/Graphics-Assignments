#include "Model.hpp"

using namespace std;

Model::Model(GLuint vPosition, GLuint vColor){
  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);
  glEnableVertexAttribArray(vPosition);
  glEnableVertexAttribArray(vColor);
  
  attrib_pos = vPosition;
  attrib_col = vColor;
}

void Model::fromFile(char* filename){
	FILE *inpFile = fopen(filename, "r");
  glm::vec3 contact_point;
  int no_of_parts;
  vector<Part*>parts(no_of_parts);
  fscanf(inpFile,"%d",&no_of_parts);
  int first_part,second_part;
  for(int i=0;i<no_of_parts;i++){
    parts[i] = new Part();
    char name[100];
    fscanf(inpFile,"%s",name);
    parts[i]->fromFile(name);
  }
  root = parts[0];
  for(int i=0;i<no_of_parts-1;i++){
    fscanf(inpFile,"%d %d %f %f %f",&first_part,&second_part,&contact_point[0],&contact_point[1],&contact_point[2]);
    Joint* joint = new Joint(parts[first_part],parts[second_part],contact_point);
    parts[first_part]->addJoint(joint);
  }
}

void Model::draw(){
  glBindVertexArray (vao);
  root -> draw(id);
}