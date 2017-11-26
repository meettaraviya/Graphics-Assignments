#include "Model.hpp"
#include <fstream>

using namespace std;

unsigned char * loadTexture( const char * filename, unsigned int &w, unsigned int &h, GLuint &texture)
{
    unsigned char header[54];
    int pos;

    unsigned int size;
    unsigned char * data;
    FILE * file;

    file = fopen( filename, "rb" );

    if (fread(header,1,54,file)!=54)
    {
		printf("Incorrect BMP file\n");
		return 0;
    }


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

    fread( data, size, 1, file );
    fclose( file );

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

void Character::renderOne(int i, glm::mat4 par_transform, glm::mat4 parent_rotate){	

	for(int i=0; i<parts.size(); i++){
		if(glfwGetKey(window, GLFW_KEY_0+i)==GLFW_PRESS){
			for(int j=0; j<6; j++){
		      if(glfwGetKey(window, relative_rot_keys[j])==GLFW_PRESS){
		      	val_rot[i][j/2] += ((j%2) ? -1 : 1)*relative_rot_speed;
		      }
			}
		}
	}
	// for( int k=0; k<3; k++)
	// 	cout << val_rot[i][k] << " ";
	// cout << endl;

	glm::mat4 my_rotate = id;
	for(int j=0; j<3; j++)
		my_rotate = glm::rotate(id, val_rot[i][j], World::axes[2*j])*my_rotate;

	glm::mat4 my_transform = id;
	my_transform = glm::translate(id, glm::vec3(attach_points[i])) * my_rotate
				   * (glm::translate(id, -glm::vec3(attach_points[i])));

	glm::mat4 model_view_transform = RealView::mat_proj * RealView::mat_lookat * World::mat_translation * 
									World::mat_rotation * par_transform * my_transform;

	glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(model_view_transform));

	glBindBuffer (GL_ARRAY_BUFFER, parts[i]->vbo);

	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(parts[i]->vertices.size()*sizeof(glm::vec4)) );
	glVertexAttribPointer( vUV, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(parts[i]->vertices.size()*sizeof(glm::vec4)*2) );


	if(parts[i]->num_textured>0){
		glUseProgram( shaderProgram );
		glUniform1i(vIsTextured, 1);
		glBindTexture( GL_TEXTURE_2D, parts[i]->texture );
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, parts[i]->texture_width, parts[i]->texture_height, 0, GL_BGR, GL_UNSIGNED_BYTE, parts[i]->texture_data);

		glDrawArrays(draw_mode, 0, parts[i]->num_textured);

	}else{
		glUseProgram( shaderProgram );
		glUniform1i(vIsTextured, 0);
		glDrawArrays(draw_mode, parts[i]->num_textured, parts[i]->vertices.size()-parts[i]->num_textured);

	}
	for(auto j : tree[i]){
		renderOne(j, par_transform * my_transform, my_rotate);
	}
}

void Character::render(){
	glBindVertexArray (vao);
	renderOne(0, id, id);
}

void Character::update(){

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

  // cout << inFileName << endl;
  // for(int i=0; i<5; i++)
  //   cout << part->vertices[i].x << " " << part->vertices[i].y << " " << part->vertices[i].z << " " << endl;
  // cout << endl;

  val_rot.push_back(glm::vec3());
  attach_points.push_back(glm::vec4(0,0,0,0));
  tree.push_back(vector<int>());

  parts.push_back(part);
  fclose(inpFile);
}

void Character::addJoint(int i, int j, glm::vec3 attach_point){
	tree[i].push_back(j);
	attach_points[j] = glm::vec4(attach_point,0);
}

void Character::loadCharacter(char* charFileName){
  FILE *charFile = fopen(charFileName, "r");
  char rawFileName[20];
  int count;
  fscanf(charFile, "%d", &count);
  for(int i=0;i<count;i++){
    fscanf(charFile,"%s",rawFileName);
    fromFile(rawFileName);
    loadBuffers(i);
  }
  int l, r;
  glm::vec3 pos;
  for(int i=0; i<count-1; i++){
    fscanf( charFile, "%d %d %f %f %f", &l, &r, &pos.x, &pos.y, &pos.z);
    addJoint(l, r, pos);
  }

  char textureFile[100];
  // fscanf(charFile, "%s" , textureFile);

  // GLuint texture = loadTexture(textureFile);

  fclose(charFile);

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

	// cout << inFileName << endl;
	// for(int i=0; i<5; i++)
	// 	cout << part->vertices[i].x << " " << part->vertices[i].y << " " << part->vertices[i].z << " " << endl;
	// cout << endl;

	parts.push_back(part);
	fclose(inpFile);
}

void Character::send_params(int &ix, vector<GLfloat> &params){
	   //  for(int i=0; i<params.size(); i++){
    //   cout << params[i] << " ";
    // }
    // cout << endl;
	for(int i=0; i<val_rot.size(); i++){
		params[ix] = val_rot[i][0];
		params[ix+1] = val_rot[i][1];
		params[ix+2] = val_rot[i][2];
		ix+=3;
	}
	params[ix] = vec_rotate[0];
	params[ix+1] = vec_rotate[1];
	params[ix+2] = vec_rotate[2];
	ix += 3;
	params[ix] = vec_scale[0];
	params[ix+1] = vec_scale[1];
	params[ix+2] = vec_scale[2];
	ix += 3;
	params[ix] = vec_translate[0];
	params[ix+1] = vec_translate[1];
	params[ix+2] = vec_translate[2];
	ix += 3;
	   //  for(int i=0; i<params.size(); i++){
    //   cout << params[i] << " ";
    // }
    // cout << endl;
}

void Character::get_params(int &ix, vector<GLfloat> &params){
	for(int i=0; i<val_rot.size(); i++){
		val_rot[i][0] = params[ix];
		val_rot[i][1] = params[ix+1];
		val_rot[i][2] = params[ix+2];
		ix+=3;
	}
	vec_rotate[0] = params[ix];
	vec_rotate[1] = params[ix+1];
	vec_rotate[2] = params[ix+2];
	ix += 3;
	vec_scale[0] = params[ix];
	vec_scale[1] = params[ix+1];
	vec_scale[2] = params[ix+2];
	ix += 3;
	vec_translate[0] = params[ix];
	vec_translate[1] = params[ix+1];
	vec_translate[2] = params[ix+2];
	ix += 3;
}
