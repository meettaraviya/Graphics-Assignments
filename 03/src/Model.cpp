#include "Model.hpp"

using namespace std;

void Model::fromFile(char* filename){
  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);
  glEnableVertexAttribArray(vPosition);
  glEnableVertexAttribArray(vColor);

	FILE *inpFile = fopen(filename, "r");
  glm::vec3 contact_point;
  int no_of_parts;
  fscanf(inpFile,"%d",&no_of_parts);
  vector<Part*>parts(no_of_parts);
  int first_part,second_part;

  glBindVertexArray (vao);

  for(int i=0;i<no_of_parts;i++){
    parts[i] = new Part();
    parts[i] -> loadBuffers();
    char name[100];
    fscanf(inpFile,"%s",name);
    parts[i]->fromFile(name);
  }
  root = parts[0];
  for(int i=0;i<no_of_parts-1;i++){
    fscanf(inpFile,"%d %d %f %f %f",&first_part,&second_part,&contact_point[0],&contact_point[1],&contact_point[2]);
    parts[first_part]->joinTo(parts[second_part],contact_point);
  }
}

void Part::loadBuffers(){
  glGenBuffers (1,&vbo);
  glBindBuffer (GL_ARRAY_BUFFER,vbo);

  glBufferData (GL_ARRAY_BUFFER, (vertices.size() + colors.size()) * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec4), vertices.data() );
  glBufferSubData( GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec4), colors.size() * sizeof(glm::vec4), colors.data() );

  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size()*sizeof(glm::vec4)) );

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::draw(){
  glBindVertexArray (vao);
  // cout << "vao = " << vao << endl;
  root -> draw(id);
}

void Part::fromFile(char* inFileName){
  FILE *inpFile = fopen(inFileName, "r");
  glm::vec4 pos(0.0,0.0,0.0,1.0), col(0.0,0.0,0.0,1.0);
  
  while(fscanf(inpFile,"%f %f %f %f %f %f",&pos[0],&pos[1],&pos[2],&col[0],&col[1],&col[2])>0){
    vertices.push_back(pos);
    colors.push_back(col);
  }
  fclose(inpFile);
}

void Part::draw(glm::mat4 mat_parent_transform){
  glBindVertexArray(2);
  glm::mat4 mat_transform = glm::translate(id, attach_point) * mat_rotation * glm::translate(id, -attach_point)*mat_parent_transform;
  // glUniformMatrix4fv(uPartMatrix, 1, GL_FALSE, glm::value_ptr(mat_transform));
  glUniformMatrix4fv(uPartMatrix, 1, GL_FALSE, glm::value_ptr(id));

  glBindBuffer (GL_ARRAY_BUFFER,vbo);
  // cout << vbo << endl;
  // cout << vertices.size() << endl;

  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertices.size()*sizeof(glm::vec4)) );
  
  glDrawArrays(GL_TRIANGLES, 0, vertices.size());

  // cout << this << endl;

  for(int i=0;i<joined_parts.size();i++){
    joined_parts[i]->draw(mat_transform);
  }
}

void Part::joinTo(Part* part, glm::vec3 attach_point){
  joined_parts.push_back(part);
}
