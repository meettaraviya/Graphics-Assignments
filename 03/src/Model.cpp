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
}
=======
unsigned char * loadTexture( const char * filename, unsigned int &w, unsigned int &h, GLuint &texture)
{
    unsigned char header[54];// 54 Byte header of BMP
    int pos;
    // unsigned int w,h;
    unsigned int size; //w*h*3
    unsigned char * data; // Data in RGB FORMAT
    FILE * file;
    
    file = fopen( filename, "rb" );
    // if ( file == NULL ) return 0;  // if file is empty 
    if (fread(header,1,54,file)!=54)
      {
  printf("Incorrect BMP file\n");
  return 0;
      }

    // Read  MetaData
    pos = *(int*)&(header[0x0A]);
    size = *(int*)&(header[0x22]);
    w = *(int*)&(header[0x12]);
    h = *(int*)&(header[0x16]);

    //Just in case metadata is missing
    if(size == 0) 
      size = w*h*3;
    if(pos == 0)
      pos = 54;

    data = new unsigned char [size];

    // cout << "fread" << 
    fread( data, size, 1, file );// << endl; // read the file
    fclose( file );
    //////////////////////////

    glGenTextures( 1, &texture );

    glBindTexture( GL_TEXTURE_2D, texture );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
   

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    
    return data;// return the texture id
}


Model::Model(int shape){
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(vColor);
	glEnableVertexAttribArray(vUV);
	
	draw_mode = shape;
}

Character::Character(int shape){
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(vColor);
	glEnableVertexAttribArray(vUV);
	
	draw_mode = shape;
}

void Model::loadBuffers(int index){
	Part* part = parts[index];
	glBindVertexArray (vao);
	glGenBuffers (1, &part->vbo);
	glBindBuffer (GL_ARRAY_BUFFER, part->vbo);

	glBufferData (GL_ARRAY_BUFFER, part->uvs.size()*sizeof(glm::vec2) + (part->vertices.size() + part->colors.size()) * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBufferSubData( GL_ARRAY_BUFFER, 0, part->vertices.size() * sizeof(glm::vec4), part->vertices.data() );
	glBufferSubData( GL_ARRAY_BUFFER, part->vertices.size() * sizeof(glm::vec4), part->colors.size() * sizeof(glm::vec4), part->colors.data() );
	glBufferSubData( GL_ARRAY_BUFFER, part->vertices.size() * sizeof(glm::vec4) + part->colors.size() * sizeof(glm::vec4), part->uvs.size() * sizeof(glm::vec2), part->uvs.data() );

	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(part->vertices.size()*sizeof(glm::vec4)) );
	glVertexAttribPointer( vUV, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(part->vertices.size()*sizeof(glm::vec4)*2) );

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Model::render(){

	glBindVertexArray (vao);

	for(int i=0; i<parts.size(); i++){

		glBindBuffer (GL_ARRAY_BUFFER, parts[i]->vbo);

		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(parts[i]->vertices.size()*sizeof(glm::vec4)) );
		glVertexAttribPointer( vUV, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(parts[i]->vertices.size()*sizeof(glm::vec4)*2) );
		
		glDrawArrays(draw_mode, 0, parts[i]->vertices.size());
	}
	
}

void Character::renderOne(int i, glm::mat4 parent_transform){


	glm::vec3 new_axes[6];
	glm::mat4 mat_mult_left = RealView::mat_proj * 
	                    RealView::mat_lookat *
	                    World::mat_translation *
	                    World::mat_rotation;
	glm::vec3 vec_translate(parent_transform * attach_points[i] );

	for(int i=0; i<6; i++)
		new_axes[i] = glm::vec3(mat_mult_left*parent_transform*glm::vec4(World::axes[i],1.0));

	for(int i=0; i<parts.size(); i++){
		if(glfwGetKey(window, GLFW_KEY_0+i)==GLFW_PRESS){
			for(int j=0; j<6; j++){
		      if(glfwGetKey(window, relative_rot_keys[j])==GLFW_PRESS){
		      	mats_relative_rot[i] = glm::rotate(id, relative_rot_speed, World::axes[j])*mats_relative_rot[i]; 	
		      }
			}
		}
	}

	glm::mat4 my_transform = 
		glm::translate(id, vec_translate) *
		mats_relative_rot[i] *
		glm::translate(id, -vec_translate) *
		parent_transform;

	// cout << i << " " << my_transform[0][0] << " " << my_transform[0][1] << " " << my_transform[0][2] << " " << endl;

	glm::mat4 modelview_matrix = mat_mult_left * my_transform;
	
	glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

	glBindBuffer (GL_ARRAY_BUFFER, parts[i]->vbo);

	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(parts[i]->vertices.size()*sizeof(glm::vec4)) );
	glVertexAttribPointer( vUV, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(parts[i]->vertices.size()*sizeof(glm::vec4)*2) );


	if(parts[i]->num_textured>0){
		// cout << i << " " << parts[i]->num_textured << endl;
		glm::vec4 one(1,1,1,1);
		glUniform4fv(vIsTextured, 1, &one[0]);
		// cout << (long int)parts[i]->texture_data << endl;
		glBindTexture( GL_TEXTURE_2D, parts[i]->texture );
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, parts[i]->texture_width, parts[i]->texture_height, 0, GL_BGR, GL_UNSIGNED_BYTE, parts[i]->texture_data);	

		glDrawArrays(draw_mode, 0, parts[i]->num_textured);
	}else{
	
	glm::vec4 zero(0,0,0,0);
	glUniform4fv(vIsTextured, 1, &zero[0]);

	
	glDrawArrays(draw_mode, parts[i]->num_textured, parts[i]->vertices.size()-parts[i]->num_textured);

	}
	for(auto j : tree[i]){
		renderOne(j, my_transform);
	}
}

void Character::render(){

	glBindVertexArray (vao);

	renderOne(0, id);
	
}

void Character::update(){

}

void Character::addJoint(int i, int j, glm::vec3 attach_point){
	tree[i].push_back(j);
	attach_points[j] = glm::vec4(attach_point,0);
}

void Character::fromFile(char* inFileName){

	FILE *inpFile = fopen(inFileName, "r");
	glm::vec4 pos(0.0,0.0,0.0,1.0), col(0.0,0.0,0.0,1.0);
	glm::vec2 uvs;
	int textured;
	Part* part = new Part;

	fscanf(inpFile,"%d",&(part->num_textured));
	if(part->num_textured>0){
		char textureFile[100];
		fscanf(inpFile, "%s", textureFile);
		part->texture_data = loadTexture(textureFile, part->texture_width, part->texture_height, part->texture);

	}
	
	while(fscanf(inpFile,"%f %f %f %f %f %f %d %f %f",&pos[0],&pos[1],&pos[2],&col[0],&col[1],&col[2], &textured, &uvs[0], &uvs[1])>0){
		part->vertices.push_back(pos);
		part->colors.push_back(col);
		// part->textured.push_back(textured);
		part->uvs.push_back(uvs);
	}

	cout << inFileName << endl;
	for(int i=0; i<5; i++)
		cout << part->vertices[i].x << " " << part->vertices[i].y << " " << part->vertices[i].z << " " << endl;
	cout << endl; 

	mats_relative_rot.push_back(id);
	attach_points.push_back(glm::vec4(0,0,0,0)); 
	tree.push_back(vector<int>());

	parts.push_back(part);
	fclose(inpFile);
}


void Model::fromFile(char* inFileName){

	FILE *inpFile = fopen(inFileName, "r");
	glm::vec4 pos(0.0,0.0,0.0,1.0), col(0.0,0.0,0.0,1.0);
	glm::vec2 uvs;
	int textured;
	Part* part = new Part;

	fscanf(inpFile,"%d",&(part->num_textured));
	if(part->num_textured>0){
		char textureFile[100];
		fscanf(inpFile, "%s", textureFile);
		part->texture_data = loadTexture(textureFile, part->texture_width, part->texture_height, part->texture);
	}
	
	while(fscanf(inpFile,"%f %f %f %f %f %f %d %f %f",&pos[0],&pos[1],&pos[2],&col[0],&col[1],&col[2], &textured, &uvs[0], &uvs[1])>0){
		part->vertices.push_back(pos);
		part->colors.push_back(col);
		part->uvs.push_back(uvs);
	}

	cout << inFileName << endl;
	for(int i=0; i<5; i++)
		cout << part->vertices[i].x << " " << part->vertices[i].y << " " << part->vertices[i].z << " " << endl;
	cout << endl; 

	parts.push_back(part);
	fclose(inpFile);
}
>>>>>>> NEW
