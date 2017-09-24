#include "Model.hpp"

using namespace std;

Model::Model(GLuint vPosition, GLuint vColor, GLuint vArray, int shape){
	draw_mode = shape;
	attrib_pos = vPosition;
	attrib_col = vColor;
	vao = vArray;
}

void Model::fromFile(string inFileName){

	FILE *inpFile = fopen(inFileName.c_str(), "r");
	glm::vec4 pos(0.0,0.0,0.0,1.0), col(0.0,0.0,0.0,1.0);
	Part* part = new Part;

	while(fscanf(inpFile,"%f %f %f %f %f %f",&pos[0],&pos[1],&pos[2],&col[0],&col[1],&col[2])>0){
		part->vertices.push_back(pos);
		part->colors.push_back(col);
	}

	fclose(inpFile);

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

	parts.push_back(part);

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