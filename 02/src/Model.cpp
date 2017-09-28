#include "Model.hpp"

using namespace std;

Model::Model(GLuint vPosition, GLuint vColor, int shape){
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

LineArray::LineArray(GLuint vPosition, GLuint vColor){
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(vColor);
	
	draw_mode = GL_LINES;
	attrib_pos = vPosition;
	attrib_col = vColor;
}

void LineArray::loadFrustum(){
	Part *part = new Part;

	glm::vec3 right = glm::cross(View::lookat,View::up);
	glm::vec3 n = View::getN(), u = View::getU(), v = View::getV();
	vector <glm::vec3>temp({
		-(n*View::n) + (v*View::t) - (u*View::r),
		-(n*View::n) + (v*View::t) - (u*View::l),
		-(n*View::n) + (v*View::b) - (u*View::r),
		-(n*View::n) + (v*View::b) - (u*View::l)
	});
	for(int i=0;i<4;i++){
		temp.push_back(temp[i]*(View::f/View::n) + View::eye);
		temp[i] += View::eye;
	}
	temp.push_back(View::eye);
	vector <glm::vec4> colors = std::vector<glm::vec4>({
		{0,1,1,1},{1,0,1,1},{0,0,0,1}
	});
	vector<pair<int,int>> lines({
		{0,1},{1,3},{3,2},{2,0},{4,5},{5,7},{7,6},{6,4},{0,4},{1,5},{2,6},{3,7},{8,0},{8,1},{8,2},{8,3}
	});
	vector <int> color_index({2,2,2,2,2,2,2,2,0,0,0,0,1,1,1,1});
	for(int i=0;i<16;i++){
		part->vertices.push_back(glm::vec4(temp[lines[i].first],1.0));
		part->vertices.push_back(glm::vec4(temp[lines[i].second],1.0));
		part->colors.push_back(colors[color_index[i]]);
		part->colors.push_back(colors[color_index[i]]);
	}
	parts.push_back(part);

	glLineWidth(lineWidth);
}

void LineArray::loadAxes(){
	Part *part = new Part;

	glm::vec4 axisPoint(0.0,0.0,0.0,1.0);
	for(int i=0; i<3; i++){
		part->vertices.push_back(axisPoint);
		axisPoint[i] = lineLength;
		part->vertices.push_back(axisPoint);
		axisPoint[i] = 0.0;
		// part->colors.push_back(axesColors[2*i]);
		// part->colors.push_back(axesColors[2*i+1]);
	}
	parts.push_back(part);

	glLineWidth(lineWidth);
}

PointArray::PointArray(GLuint vPosition, GLuint vColor){
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(vColor);
	
	draw_mode = GL_POINTS;
	attrib_pos = vPosition;
	attrib_col = vColor;
}

void PointArray::fromPoint(glm::vec3 point, glm::vec4 color){
	Part* part = new Part;	
	part->vertices.push_back(glm::vec4(point,1.0));
	part->colors.push_back(color);
	parts.push_back(part);
	glPointSize(pointSize);
}