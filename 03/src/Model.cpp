#include "Model.hpp"

using namespace std;

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

void Model::fromFile(char* inFileName){

	FILE *inpFile = fopen(inFileName, "r");
	glm::vec4 pos(0.0,0.0,0.0,1.0), col(0.0,0.0,0.0,1.0);
	glm::vec2 uvs;
	int textured;
	Part* part = new Part;
	
	while(fscanf(inpFile,"%f %f %f %f %f %f %d %f %f",&pos[0],&pos[1],&pos[2],&col[0],&col[1],&col[2], &textured, &uvs[0], &uvs[1])>0){
		part->vertices.push_back(pos);
		part->colors.push_back(col);
		part->textured.push_back(textured);
		part->uvs.push_back(uvs);
	}

	parts.push_back(part);
	fclose(inpFile);
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

	glm::vec3 vec_translate( parent_transform * attach_points[i] );

	glm::vec3 new_axes[6];

	for(int i=0; i<6; i++)
		new_axes[i] = glm::vec3(parent_transform*glm::vec4(World::axes[i],1.0));

	for(int i=0; i<parts.size(); i++){
		if(glfwGetKey(window, GLFW_KEY_0+i)==GLFW_PRESS){
			for(int j=0; j<6; j++){
		      if(glfwGetKey(window, relative_rot_keys[j])==GLFW_PRESS){
		      	// cout << i << j << endl;
		      	mats_relative_rot[i] = glm::rotate(id, relative_rot_speed, new_axes[j])*mats_relative_rot[i]; 	
		      }
			}
		}
	}

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

	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(parts[i]->vertices.size()*sizeof(glm::vec4)) );
	glVertexAttribPointer( vUV, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(parts[i]->vertices.size()*sizeof(glm::vec4)*2) );
	
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

}

void Character::addJoint(int i, int j, glm::vec3 attach_point){
	tree[i].push_back(j);
	attach_points[j] = glm::vec4(attach_point,0);
}

GLuint loadTexture( const char * filename, int width, int height )
{
    GLuint texture;
    unsigned char header[54];// 54 Byte header of BMP
    int pos;
    unsigned int w,h;
    unsigned int size; //w*h*3
    unsigned char * data; // Data in RGB FORMAT
    FILE * file;
    
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;  // if file is empty 
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

    fread( data, size, 1, file ); // read the file
    fclose( file );
    //////////////////////////

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
   

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    
    free( data );
    return texture;// return the texture id
}


void Character::fromFile(char* inFileName){

	FILE *inpFile = fopen(inFileName, "r");
	glm::vec4 pos(0.0,0.0,0.0,1.0), col(0.0,0.0,0.0,1.0);
	glm::vec2 uvs;
	int textured;
	Part* part = new Part;
	
	while(fscanf(inpFile,"%f %f %f %f %f %f %d %f %f",&pos[0],&pos[1],&pos[2],&col[0],&col[1],&col[2], &textured, &uvs[0], &uvs[1])>0){
		part->vertices.push_back(pos);
		part->colors.push_back(col);
		part->textured.push_back(textured);
		part->uvs.push_back(uvs);
	}

	mats_relative_rot.push_back(id);
	attach_points.push_back(glm::vec4(0,0,0,0)); 
	tree.push_back(vector<int>());

	parts.push_back(part);
	fclose(inpFile);


}
