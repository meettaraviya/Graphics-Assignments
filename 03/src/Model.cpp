#include "Model.hpp"

using namespace std;

<<<<<<< HEAD
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
=======
Model::Model(GLuint vPosition, GLuint vColor, int shape){
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(vColor);
	
	draw_mode = shape;
	attrib_pos = vPosition;
	attrib_col = vColor;
}

Character::Character(GLuint vPosition, GLuint vColor, int shape){
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(vColor);
	
	draw_mode = shape;
	attrib_pos = vPosition;
	attrib_col = vColor;
}

void Model::fromFile(char* inFileName){

	FILE *inpFile = fopen(inFileName, "r");
	glm::vec4 pos(0.0,0.0,0.0,1.0), col(0.0,0.0,0.0,1.0);
	Part* part = new Part;
	
	while(fscanf(inpFile,"%f %f %f %f %f %f",&pos[0],&pos[1],&pos[2],&col[0],&col[1],&col[2])>0){
		part->vertices.push_back(pos);
		part->colors.push_back(col);
	}

	parts.push_back(part);
	fclose(inpFile);
}

void Model::loadBuffers(int index){
	Part* part = parts[index];
	glBindVertexArray (vao);
	glGenBuffers (1, &part->vbo);
	glBindBuffer (GL_ARRAY_BUFFER, part->vbo);

	glBufferData (GL_ARRAY_BUFFER, (part->vertices.size() + part->colors.size()) * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBufferSubData( GL_ARRAY_BUFFER, 0, part->vertices.size() * sizeof(glm::vec4), part->vertices.data() );
	glBufferSubData( GL_ARRAY_BUFFER, part->vertices.size() * sizeof(glm::vec4), part->colors.size() * sizeof(glm::vec4), part->colors.data() );

	// glEnableVertexAttribArray(attrib_pos);
	glVertexAttribPointer( attrib_pos, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	// glEnableVertexAttribArray(attrib_col);
	glVertexAttribPointer( attrib_col, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(part->vertices.size()*sizeof(glm::vec4)) );

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Model::render(){

	glBindVertexArray (vao);

	for(int i=0; i<parts.size(); i++){

		glBindBuffer (GL_ARRAY_BUFFER, parts[i]->vbo);

		glVertexAttribPointer( attrib_pos, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
		glVertexAttribPointer( attrib_col, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(parts[i]->vertices.size()*sizeof(glm::vec4)) );
		
		glDrawArrays(draw_mode, 0, parts[i]->vertices.size());
	}
	
}

void Character::renderOne(int i, glm::mat4 parent_transform){

	glm::vec3 vec_translate( parent_transform * attach_points[i] ); 

	glm::mat4 my_transform = 
		glm::translate(id, vec_translate) *
		mats_relative_rot[i] *
		glm::translate(id, -vec_translate) *
		parent_transform;

	cout << i << " " << my_transform[0][0] << " " << my_transform[0][1] << " " << my_transform[0][2] << " " << endl;

	glm::mat4 modelview_matrix = RealView::mat_proj * 
	                    RealView::mat_lookat *
	                    World::mat_translation *
	                    World::mat_rotation *
	                    my_transform;
	
	glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
	
	glBindBuffer (GL_ARRAY_BUFFER, parts[i]->vbo);

	glVertexAttribPointer( attrib_pos, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	glVertexAttribPointer( attrib_col, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(parts[i]->vertices.size()*sizeof(glm::vec4)) );
	
	glDrawArrays(draw_mode, 0, parts[i]->vertices.size());

	for(auto j : tree[i]){
		renderOne(j, my_transform);
	}
}

void Character::render(){

	glBindVertexArray (vao);

	renderOne(0, id);
	
}

void Character::update(){
	for(int i=0; i<parts.size(); i++){
		if(glfwGetKey(window, GLFW_KEY_0+i)==GLFW_PRESS){
			for(int j=0; j<6; j++){
		      if(glfwGetKey(window, relative_rot_keys[j])==GLFW_PRESS){
		      	// cout << i << j << endl;
		      	mats_relative_rot[i] = glm::rotate(id, relative_rot_speed, World::axes[j])*mats_relative_rot[i]; 	
		      }
			}
		}
	}
}

void Character::addJoint(int i, int j, glm::vec3 attach_point){
	tree[i].push_back(j);
	attach_points[j] = glm::vec4(attach_point,0);
}

void Character::fromFile(char* inFileName){

	FILE *inpFile = fopen(inFileName, "r");
	glm::vec4 pos(0.0,0.0,0.0,1.0), col(0.0,0.0,0.0,1.0);
	Part* part = new Part;
	
	while(fscanf(inpFile,"%f %f %f %f %f %f",&pos[0],&pos[1],&pos[2],&col[0],&col[1],&col[2])>0){
		part->vertices.push_back(pos);
		part->colors.push_back(col);
	}

	parts.push_back(part);
	attach_points.push_back(glm::vec4(0,0,0,0));
	mats_relative_rot.push_back(id);
	tree.push_back(vector<int>());
	fclose(inpFile);
>>>>>>> d95e54389d24f980f7e8dea61f115a16b1699a64
}
